
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <cbor.h>

#include <openssl/ssl.h>

#include <getopt.h>

#include <iostream>
#include <iomanip>
#include <vector>

enum class Format
{
    Hex,
    Dec
};

#define APP_X509_BUFF_LEN (1024 * 2)
#define APP_ATTDOC_BUFF_LEN (1024 * 10)

void syntactic_validation(const unsigned char *);
void cbor_worker(const cbor_item_t *);
void parse_cbor_map(const cbor_item_t *);
void parse_cbor_array(const cbor_item_t *);
void parse_cbor_bytestring(const cbor_item_t *);
void parse_cbor_tag(const cbor_item_t *);
void print_buffer(const unsigned char *buffer, size_t size, Format format = Format::Hex);

int gverbose = 0;

void output_handler(char *msg)
{
    fprintf(stdout, "\r\n%s\r\n", msg);
}

void output_handler_bytes(uint8_t *buffer, int buffer_size)
{
    for (int i = 0; i < buffer_size; i++)
        fprintf(stdout, "%02X", buffer[i]);
    fprintf(stdout, "\r\n");
}

int read_file(unsigned char *file, char *file_name, size_t elements)
{
    FILE *fp;
    size_t file_len = 0;
    fp = fopen(file_name, "r");
    file_len = fread(file, sizeof(char), elements, fp);
    if (ferror(fp) != 0)
    {
        fputs("Error reading file", stderr);
    }
    fclose(fp);
    return file_len;
}

void instrument(const char *name, cbor_item_t *cbor_item)
{
    if (gverbose)
        fprintf(stdout, "%s\r\n", name);

    if (false)
    {

        cbor_describe(cbor_item, stdout);
    }
}

int main(int argc, char *argv[])
{
    // STEP 0 - LOAD ATTESTATION DOCUMENT

    struct option long_options[] = {
        {"verbose",
         required_argument,
         0,
         'v'},
        {0,
         0,
         0,
         0}};

    int opt;
    while ((opt = getopt_long(argc, argv, "v:", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'v':
            gverbose = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-v level] <NE attestation doc>\n", argv[0]);
            exit(1);
        }
    }

    if (optind >= argc)
    {
        fprintf(stderr, "Error: Attestation document file is required\n");
        fprintf(stderr, "Usage: %s [-v level] <NE attestation doc>\n", argv[0]);
        exit(1);
    }

    // Load file into buffer
    unsigned char *att_doc_buff = (unsigned char *)malloc(APP_ATTDOC_BUFF_LEN);
    if (!att_doc_buff)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    int att_doc_len = read_file(att_doc_buff, argv[optind], APP_ATTDOC_BUFF_LEN);
    if (att_doc_len <= 0)
    {
        fprintf(stderr, "Error: Failed to read attestation document\n");
        free(att_doc_buff);
        exit(1);
    }

    if (gverbose)
    {
        printf("Verbose level: %d\n", gverbose);
        printf("Reading attestation document: %s\n", argv[optind]);
        printf("Document size: %d bytes\n", att_doc_len);
    }

    syntactic_validation(att_doc_buff);

    // Parse buffer using library
    struct cbor_load_result ad_result;
    cbor_item_t *ad_item = cbor_load(att_doc_buff, att_doc_len, &ad_result);
    free(att_doc_buff); // not needed anymore

    instrument("Attestation document", ad_item);
    cbor_worker(ad_item);
    parse_cbor_array(ad_item);

    // Parse protected header -> item 0
    cbor_item_t *ad_pheader = cbor_array_get(ad_item, 0);

    instrument("Protected header", ad_pheader);
    cbor_worker(ad_pheader);
    parse_cbor_bytestring(ad_pheader);

    size_t ad_pheader_len = cbor_bytestring_length(ad_pheader);
    // Example 04: Check that the protected header is exactly 4 bytes long
    assert(ad_pheader_len == 4);

    // Parse signed bytes -> item 2 (skip un-protected headers as they are always empty)
    cbor_item_t *ad_signed = cbor_array_get(ad_item, 2);

    instrument("Signed bytes (item 2)", ad_signed);
    cbor_worker(ad_signed);
    parse_cbor_bytestring(ad_signed);

    size_t ad_signed_len = cbor_bytestring_length(ad_signed);

    // Load signed bytes as a new CBOR object
    unsigned char *ad_signed_d = cbor_bytestring_handle(ad_signed);
    struct cbor_load_result ad_signed_result;
    cbor_item_t *ad_signed_item = cbor_load(ad_signed_d, ad_signed_len, &ad_signed_result);

    instrument("Signed item", ad_signed_item);
    cbor_worker(ad_signed_item);
    parse_cbor_map(ad_signed_item);

    // Create the pair structure and get map size
    struct cbor_pair *ad_signed_item_pairs = cbor_map_handle(ad_signed_item);
    size_t num_pairs = cbor_map_size(ad_signed_item);
    if (gverbose)
        printf("Number of key-value pairs in map: %zu\n", num_pairs);

    // Example 01: Check that the first item's key is the string "module_id" and that is not empty
    size_t module_k_len = cbor_string_length(ad_signed_item_pairs[0].key);
    unsigned char *module_k_str = (unsigned char *)realloc(cbor_string_handle(ad_signed_item_pairs[0].key), module_k_len + 1); // null char
    module_k_str[module_k_len] = '\0';
    size_t module_v_len = cbor_string_length(ad_signed_item_pairs[0].value);
    unsigned char *module_v_str = (unsigned char *)realloc(cbor_string_handle(ad_signed_item_pairs[0].value), module_v_len + 1); // null char
    module_v_str[module_v_len] = '\0';
    assert(module_k_len != 0);
    assert(module_v_len != 0);

    // Example 02: Check that the module id key is actually the string "module_id"
    assert(!strcmp("module_id", (const char *)module_k_str));

    /*

    // Print all key-value pairs from the signed document
    size_t pair_count = cbor_map_size(ad_signed_item);
    for (size_t i = 0; i < pair_count; i++)
    {
        size_t key_len = cbor_string_length(ad_signed_item_pairs[i].key);
        unsigned char *key_str = (unsigned char *)realloc(cbor_string_handle(ad_signed_item_pairs[i].key), key_len + 1);
        key_str[key_len] = '\0';

        size_t value_len = cbor_string_length(ad_signed_item_pairs[i].value);
        // unsigned char *value_str = (unsigned char *)realloc(cbor_string_handle(ad_signed_item_pairs[i].value), value_len + 1);
        // value_str[value_len] = '\0';

        printf("Key %zu: %s (length: %zu)\n", i, key_str, key_len);
        printf("Value %zu length: %zu\n", i, value_len);
    }

     */

    // Original assertions for first pair only
    assert(cbor_string_length(ad_signed_item_pairs[0].key) != 0);
    assert(cbor_string_length(ad_signed_item_pairs[0].value) != 0);
    assert(!strcmp("module_id", (const char *)cbor_string_handle(ad_signed_item_pairs[0].key)));

    // Parse signature -> item 3
    cbor_item_t *ad_sig = cbor_array_get(ad_item, 3);

    instrument("Signature (item 3)", ad_sig);
    cbor_worker(ad_sig);

    size_t ad_sig_len = cbor_bytestring_length(ad_sig);
    unsigned char *ad_sig_d = cbor_bytestring_handle(ad_sig);

    // Example 03: Check that the signature is exactly 96 bytes long
    assert(ad_sig_len == 96);
}

void parse_pointer(const unsigned char *cbor_buffer, int cbor_buffer_length)
{
    // Parse buffer using library
    struct cbor_load_result load_result;
    cbor_item_t *cbor_item = cbor_load(cbor_buffer, cbor_buffer_length, &load_result);
    if (gverbose)
    {
        int *p_int = (int *)&(load_result.error);
        printf("Error code: %d\n", *p_int);
    }
    if (NULL == cbor_item)
    {
        puts(__FUNCTION__);
        print_buffer(cbor_buffer, cbor_buffer_length);
        return;
    }
    cbor_worker(cbor_item);
}

void print_buffer(const unsigned char *buffer, size_t size, Format format)
{
    // Save the current formatting state of the output stream
    std::ios_base::fmtflags original_flags = std::cout.flags();

    for (size_t i = 0; i < size; ++i)
    {
        // Print the offset at the beginning of each line
        if (i % 16 == 0)
        {
            if (i != 0)
            {
                std::cout << '\n';
            }
            std::cout << std::setw(4) << std::setfill('0') << std::right << std::dec << i << ": ";
        }

        // Print the byte value in the selected format
        if (format == Format::Hex)
        {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << " ";
        }
        else
        {
            std::cout << std::dec << std::setw(3) << static_cast<int>(buffer[i]) << " ";
        }
    }

    std::cout << '\n';

    // Restore the original formatting state
    std::cout.flags(original_flags);
}
// bytestrings are different than arrays or maps since
// they may or may not be/contain cbor items
void parse_cbor_bytestring(const cbor_item_t *cbor_bytestring)
{

    // first, make sure input is a bytestring
    if (!cbor_isa_bytestring(cbor_bytestring))
    {
        fprintf(stderr, "Error: Invalid format - expected bytestring\n");
        // cbor_decref?
        exit(1);
    }
    // get a regular pointer
    unsigned char *bytestring_p = cbor_bytestring_handle(cbor_bytestring);
    // get length
    size_t bytestring_len = cbor_bytestring_length(cbor_bytestring);
    // see if the bytestring is/contains any cbor items
    // struct cbor_load_result load_result;
    // cbor_item_t *nested_item = cbor_load(bytestring_p, bytestring_len, &load_result);
    // if (gverbose)
    //     printf("Error code: %d\n", load_result.error);
    // if (nested_item == NULL)
    // {
    //     // Parsing failed. The error is described in load_result.
    //     fprintf(stderr, "Parsing failed.\n");
    //     exit(1);
    // }
    // // Parsing succeeded. The item is valid.
    // // if (gverbose) printf("Parsing succeeded. Item is not NULL.\n");
    // enum cbor_type type = cbor_typeof(nested_item);
    // if (gverbose)
    // {
    //     printf("type: %d\n", type);
    // }

    parse_pointer(bytestring_p, bytestring_len);
}

void parse_cbor_array(const cbor_item_t *cbor_array)
{
    // Check if ad_item is a CBOR array
    if (!cbor_isa_array(cbor_array))
    {
        fprintf(stderr, "Error: Invalid format - expected array\n");
        // cbor_decref?
        exit(1);
    }

    size_t array_size = cbor_array_size(cbor_array);

    for (size_t i = 0; i < array_size; i++)
    {
        cbor_item_t *element = cbor_array_get(cbor_array, i);
        // Check type
        enum cbor_type type = cbor_typeof(element);

        if (gverbose)
        {
            printf("element %zu - type: %d\n", i, type);
        }
        cbor_worker(element);
    }
}

void parse_cbor_tag(const cbor_item_t *cbor_tag)
{
    uint64_t tag = cbor_tag_value(cbor_tag);
    if (gverbose)
    {
        fprintf(stdout, "value: %lux hex, %lu decimal \n", tag, tag);
    }
    cbor_item_t *tagged = cbor_tag_item(cbor_tag);
    cbor_worker(tagged);
}

void parse_cbor_map(const cbor_item_t *cbor_map)
{
    size_t map_size = cbor_map_size(cbor_map);
    struct cbor_pair *pairs = cbor_map_handle(cbor_map);

    for (size_t i = 0; i < map_size; i++)
    {
        // Check type of key
        enum cbor_type key_type = cbor_typeof(pairs[i].key);
        // Check type of value
        enum cbor_type value_type = cbor_typeof(pairs[i].value);

        if (gverbose)
        {
            printf("%s: Pair %zu - Key type: %d, Value type: %d\n", __FUNCTION__, i, key_type, value_type);
        }
        cbor_worker(pairs[i].key);
        cbor_worker(pairs[i].value);
    }
}

void cbor_worker(const cbor_item_t *cbor_item)
{

    switch (cbor_typeof(cbor_item))
    {
    case CBOR_TYPE_UINT:
    {
        uint64_t val = cbor_get_int(cbor_item);
        if (gverbose)
        {
            fprintf(stdout, "UINT: %lux hex, %lu decimal \n", val, val);
        }
        break;
    }

    case CBOR_TYPE_NEGINT:
    {
        uint64_t abs_val = cbor_get_int(cbor_item);
        // Note: actual value is -1 - abs_val
        if (gverbose)
        {
            fprintf(stdout, "NEGINT: %lux hex, %lu decimal \n", abs_val, abs_val);
        }
        break;
    }

    case CBOR_TYPE_BYTESTRING:
    {
        // size_t len = cbor_bytestring_length(cbor_item);
        // unsigned char *bytes = cbor_bytestring_handle(cbor_item);
        // parse_pointer(bytes, len);
        // break;

        if (gverbose)
            puts("BYTESTRING: ");
        parse_cbor_bytestring(cbor_item);
        break;
    }

    case CBOR_TYPE_STRING:
    {
        size_t str_len = cbor_string_length(cbor_item);
        unsigned char *cbor_string = (unsigned char *)realloc(cbor_string_handle(cbor_item), str_len + 1);
        cbor_string[str_len] = 0;
        if (gverbose)
        {
            fprintf(stdout, "STRING: %s\n", cbor_string);
        }
        break;
    }

    case CBOR_TYPE_ARRAY:
    {
        if (gverbose)
            puts("ARRAY: ");
        parse_cbor_array(cbor_item);
        break;
    }

    case CBOR_TYPE_MAP:
    {
        if (gverbose)
            puts("MAP: ");
        parse_cbor_map(cbor_item);
        break;
    }

    case CBOR_TYPE_TAG:
    {
        if (gverbose)
            puts("TAG: ");
        parse_cbor_tag(cbor_item);
        break;
    }

    case CBOR_TYPE_FLOAT_CTRL:
    {
        if (gverbose)
            puts("FLOAT_CTRL: ");
        if (cbor_float_ctrl_is_ctrl(cbor_item))
        {
            uint8_t ctrl = cbor_ctrl_value(cbor_item);
            if (gverbose)
                fprintf(stdout, "ctrl = %u\n", ctrl);
        }
        else
        {
            float f = cbor_float_get_float(cbor_item);
            if (gverbose)
                fprintf(stdout, "float = %f\n", f);
        }
        break;
    }
    }
}

void syntactic_validation(const unsigned char *att_doc_buff)
{

    // Check COSE TAG (skipping - not currently implemented by AWS Nitro Enclaves)
    // assert(att_doc_buff[0] == 6 <<5 | 18); // 0xD2
    // Check if this is an array of exactly 4 items
    assert(att_doc_buff[0] == (4 << 5 | 4)); // 0x84
    // Check if next item is a byte stream of 4 bytes
    assert(att_doc_buff[1] == (2 << 5 | 4)); // 0x44
    // Check is fist item if byte stream is a map with 1 item
    assert(att_doc_buff[2] == (5 << 5 | 1)); // 0xA1
    // Check that the first key of the map is 0x01
    assert(att_doc_buff[3] == 0x01); // 0x01
    // Check that value of the the first key of the map is -35 (P-384 curve)
    assert(att_doc_buff[4] == (1 << 5 | 24)); // 0x38
    assert(att_doc_buff[5] == 35 - 1);        // 0x22
    // Check that next item is a map of 0 items
    assert(att_doc_buff[6] == (5 << 5 | 0)); // 0xA0
    // Check that the next item is a byte stream and the size is a 16-bit number (dec. 25)
    assert(att_doc_buff[7] == (2 << 5 | 25)); // 0x59
    // Cast the 16-bit number
    uint16_t payload_size = att_doc_buff[8] << 8 | att_doc_buff[9];
    // Check that the item after the payload is a byte stream and the size is 8-bit number (dec. 24)
    assert(att_doc_buff[9 + payload_size + 1] == (2 << 5 | 24)); // 0x58
    // Check that the size of the signature is exactly 96 bytes
    assert(att_doc_buff[9 + payload_size + 1 + 1] == 96); // 0x60
}