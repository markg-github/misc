
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
int read_file(unsigned char *file, char *file_name, size_t elements);
void instrument(const char *name, cbor_item_t *cbor_item);

int gverbose = 0;

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

