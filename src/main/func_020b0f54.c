/* func_020b0f54 @ 0x020b0f54, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b0fa0(void *);
extern int func_020b1068(int);

void func_020b0f54(unsigned short *p)
{
    int i;
    unsigned short *q = p;
    func_020b0fa0(p);
    for (i = 0; i < 0x800; i++) {
        if (func_020b1068(*q & 0x3ff) != 0) {
            if (((*q & 0xf000) >> 12) != 7) {
                *q = 0x4010;
            }
        }
        q++;
    }
}
