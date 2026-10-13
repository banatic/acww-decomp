/* func_ov108_0229c998 @ 0x0229c998, 0x40 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229c2dc(void *self, int size);
extern void func_ov094_0229b5e8(void *dst, int a, int b, void *c);

void func_ov108_0229c998(void *self)
{
    int result = func_ov108_0229c2dc(self, 0x40);
    if (result != 0) {
        return;
    }
    {
        unsigned char f = *((unsigned char *) self + 0x2ac);
        if (f != 0 && f == 1) {
            func_ov094_0229b5e8((char *) self + 0xd50, *(int *) ((char *) self + 0xa4), *(int *) ((char *) self + 0xa8),
                                (char *) self + 0xac);
        }
    }
}
