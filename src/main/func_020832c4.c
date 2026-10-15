/* func_020832c4 @ 0x020832c4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02083320(void);

typedef struct {
    int unk_00;
    unsigned int count;
} UnkStruct_020832c4;

unsigned char *func_020832c4(UnkStruct_020832c4 *param0, unsigned int param1)
{
    unsigned char *ret = 0;
    if (param1 < param0->count) {
        unsigned char *base = func_02083320();
        unsigned int offset = param1 * 2;
        base += 8;
        base += offset;
        ret = base + 1;
    }
    return ret;
}
