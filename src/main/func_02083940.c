/* func_02083940 @ 0x02083940, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_0208399c(void);

typedef struct {
    int unk_00;
    unsigned int count;
} UnkStruct_02083940;

unsigned char *func_02083940(UnkStruct_02083940 *param0, unsigned int param1)
{
    unsigned char *ret = 0;
    if (param1 < param0->count) {
        unsigned char *base = func_0208399c();
        unsigned int offset = param1 * 8;
        base += 8;
        base += offset;
        ret = base + 4;
    }
    return ret;
}
