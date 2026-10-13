/* func_ov126_022a0904 @ 0x022a0904, 0x20 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a0904 {
    char pad_00[0xA8];
    unsigned char b;
    char pad_A9[0x419F];
    unsigned short arr[1];
};

unsigned short func_ov126_022a0904(struct UnkStruct_022a0904 *s)
{
    if (s->b == 0) {
        return 0;
    }
    return s->arr[s->b - 1];
}
