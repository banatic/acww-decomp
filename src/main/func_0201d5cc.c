/* func_0201d5cc @ 0x0201d5cc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015330(void *self, void *ctx, int a, int b, int c);
extern void func_0207df18(void *a, void *b);
extern void func_02081ac0(void *a, void *b);
extern void func_02068440(void *a);

void func_0201d5cc(void *selfv)
{
    unsigned char *self = (unsigned char *) selfv;
    void *ptr;
    void *val;

    ptr = *(void **) (self + 0x100);
    val = *(void **) ((unsigned char *) ptr + 0x830);

    func_02015330(self, self + 0x124, 0, 5, 0);

    if (val != 0) {
        if (*(unsigned short *) (self + 0x124) != 0xfff1) {
            func_0207df18(val, self + 0x124);
            if (*(void **) (self + 0x12c) != 0) {
                func_02081ac0(*(void **) (self + 0x12c), self + 0x124);
            }
        }
    }
    func_02068440(*(void **) (self + 0x40));
}
