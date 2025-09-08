
#if !defined(PARSE_CBOR_H)

#define PARSE_CBOR_H

enum class Format
{
    Hex,
    Dec
};

void cbor_worker(const cbor_item_t *);
void parse_pointer(const unsigned char *cbor_buffer, int cbor_buffer_length);
void parse_cbor_map(const cbor_item_t *);
void parse_cbor_array(const cbor_item_t *);
void parse_cbor_bytestring(const cbor_item_t *);
void parse_cbor_tag(const cbor_item_t *);
void print_buffer(const unsigned char *buffer, size_t size, Format format = Format::Hex);
int read_file(unsigned char *file, char *file_name, size_t elements);
void instrument(const char *name, cbor_item_t *cbor_item);

#endif
