/* func_020b0038 @ 0x020b0038, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b00a8(unsigned int, unsigned int, unsigned int);
extern unsigned int data_021f49f0;
extern unsigned int data_021f49f4;

void *func_020b0038(unsigned int idx, unsigned short *base, unsigned int x, unsigned int count, unsigned short *out)
{
    unsigned short *p;

    if (idx < count) {
        p = base + idx;
        if (out) {
            *out = *p;
        }
        if (func_020b00a8(idx, count, x)) {
            return &data_021f49f4;
        } else {
            return p;
        }
    } else {
        return &data_021f49f0;
    }
}
