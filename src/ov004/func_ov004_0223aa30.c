/* func_ov004_0223aa30 @ 0x0223aa30, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223ac7c(void *);
extern int func_ov004_0223ac98(void *, int, int);
extern void func_02003e80(void *);
extern void func_020e9b9c(void *);
extern void *func_02003ec8(void *, int);
extern void func_02003e90(void *);
extern unsigned char data_ov004_022595b8;

int func_ov004_0223aa30(char *self, int ch, int prog)
{
    int cur = *(short *) self & 1;
    signed char nxt;
    func_ov004_0223ac7c(self + 4 + cur * 0xa8);
    nxt = (*(short *) self + 1) & 1;
    if (func_ov004_0223ac98(self + 4 + nxt * 0xa8, ch, prog) != 0) {
        *(short *) self = nxt;
        if (data_ov004_022595b8 != 0 && *(void **) (self + 0x158) != 0) {
            void **p;
            if (*(void **) (self + 0x15c) != 0) {
                func_02003e80(*(void **) (self + 0x15c));
                *(void **) (self + 0x15c) = 0;
            }
            func_020e9b9c(*(void **) (self + 0x158));
            p = (void **) (self + 0x15c);
            *p = func_02003ec8(*(void **) (self + 0x158), ch);
            if (*p != 0) {
                func_02003e90(*p);
            }
        }
        return 1;
    }
    return 0;
}
