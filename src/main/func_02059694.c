/* func_02059694 @ 0x02059694, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205971c(void *p, int arg1, void *arg2, void *arg3, void *arg4);
extern void func_020597a8(void *p, void *arg1, void *arg2, void *arg3, void *arg4);

void func_02059694(unsigned char *p)
{
    unsigned short val;
    if ((unsigned int) p[0xc8] >= 0x0c) {
        return;
    }
    val = *(unsigned short *) (p + 0x50);
    if (val == 0xfff1) {
        return;
    }
    if ((unsigned int) p[0xd8] != 1) {
        return;
    }
    if (*(unsigned int *) (p + 0x54) == 2) {
        if ((unsigned int) val >= 0x1561 && (unsigned int) val <= 0x1564) {
            // do nothing
        } else if ((unsigned int) val >= 0x155f && (unsigned int) val <= 0x1560) {
            // do nothing
        } else {
            func_0205971c(p, 0x27, p + 0x60, p + 0xa8, p + 0xb4);
            return;
        }
    }
    func_020597a8(p, p + 0x50, p + 0x60, p + 0xa8, p + 0xb4);
}
