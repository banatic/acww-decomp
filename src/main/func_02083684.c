/* func_02083684 @ 0x02083684, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02083708(void);

typedef struct {
    int unk_00;
    unsigned int count;
} UnkStruct_02083684;

unsigned char *func_02083684(UnkStruct_02083684 *param0, unsigned int param1)
{
    unsigned char *ret = 0;
    if (param1 < param0->count) {
        unsigned char *base = func_02083708();
        unsigned int offset = param1 * 2;
        base += 8;
        base += offset;
        ret = base + 1;
    }
    return ret;
}
