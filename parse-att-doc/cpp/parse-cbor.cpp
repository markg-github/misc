
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

#include "parse-cbor.h"

#define MAX_CBOR_BUFF_LEN (1024 * 10)

int gverbose = 0;

int main(int argc, char *argv[])
{
    // STEP 0 - LOAD CBOR FILE

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
            fprintf(stderr, "Usage: %s [-v level] <CBOR file>\n", argv[0]);
            exit(1);
        }
    }

    if (optind >= argc)
    {
        fprintf(stderr, "Error: CBOR file is required\n");
        fprintf(stderr, "Usage: %s [-v level] <CBOR file>\n", argv[0]);
        exit(1);
    }

    // Load file into buffer
    unsigned char *cbor_buff = (unsigned char *)malloc(MAX_CBOR_BUFF_LEN);
    if (!cbor_buff)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    int cbor_buff_len = read_file(cbor_buff, argv[optind], MAX_CBOR_BUFF_LEN);
    if (cbor_buff_len <= 0)
    {
        fprintf(stderr, "Error: Failed to read CBOR file. \n");
        free(cbor_buff);
        exit(1);
    }

    if (gverbose)
    {
        printf("Verbose level: %d\n", gverbose);
        printf("Reading CBOR file: %s\n", argv[optind]);
        printf("Document size: %d bytes\n", cbor_buff_len);
    }

    parse_pointer(cbor_buff, cbor_buff_len);

    return 0;

    // Parse buffer using library
    struct cbor_load_result ad_result;
    cbor_item_t *ad_item = cbor_load(cbor_buff, cbor_buff_len, &ad_result);
    free(cbor_buff); // not needed anymore

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
