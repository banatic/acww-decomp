/* func_0209518c @ 0x0209518c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __arm memcmp(const void *a, const void *b, unsigned int len);

struct UnkStruct_0209518c {
    unsigned char pad_00[0x0e];
    unsigned short unk_0E;
    unsigned char data[0x0c];
    signed char unk_1C;
};

int func_0209518c(const struct UnkStruct_0209518c *a, const struct UnkStruct_0209518c *b)
{
    return (a->unk_0E == b->unk_0E) && (a->unk_1C == b->unk_1C) && (memcmp(a->data, b->data, 0xc) == 0);
}
