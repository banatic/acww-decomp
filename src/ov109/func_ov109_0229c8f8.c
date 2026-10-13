/* func_ov109_0229c8f8 @ 0x0229c8f8, 0x3c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229c2ac(void *self, int b);
extern void func_ov094_0229a6bc(void *addr, unsigned int x, unsigned int y);

void func_ov109_0229c8f8(void *self)
{
    unsigned char c;
    if (func_ov109_0229c2ac(self, 0x20) != 0) {
        return;
    }
    c = ((unsigned char *) self)[0x29cf];
    if (c == 0) {
        return;
    }
    if (c != 1) {
        return;
    }
    func_ov094_0229a6bc((void *) ((char *) self + 0xcc), *(unsigned int *) ((char *) self + 0x29c4),
                        *(unsigned int *) ((char *) self + 0x29c8));
}
