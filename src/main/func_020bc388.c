/* func_020bc388 @ 0x020bc388, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bde24(void *self);
extern void func_020bc428(void *self);
extern void func_020bc464(void *self);
extern void func_020be388(void *self);
extern void func_020bf5b8(void *p);
extern void func_0208a0c8(void *base);
extern void func_020bf700(void *p);
extern void func_020bf5f0(void *p);
extern void func_020be348(void *self);
extern void func_020bea1c(void *p);
extern void func_020be568(void *p);

void func_020bc388(void *self)
{
    char *p = (char *) self;
    char *end = (char *) self + 0x1b30;
    int *counter;
    char *base;

    func_020bde24(self);
    func_020bc428(self);
    func_020bc464(self);

    counter = (int *) ((char *) self + 0x2f14);

    while (p < end) {
        if (*(int *) (p + 8) != 0x34) {
            base = p + 0x10;
            switch (*(int *) (p + 4)) {
                case 1:
                    if (*(int *) (p + 0x24) != 6) {
                        func_020be388(self);
                    }
                    func_020bf5b8(p);
                    *(int *) (p + 4) = 2;
                    break;
                case 2:
                    func_0208a0c8(base);
                    func_020bf700(p);
                    break;
                case 3:
                    func_020bf5f0(p);
                    *counter = *counter - 1;
                    break;
                default:
                    break;
            }
        }
        p += 0x74;
    }

    func_020be348(self);
    func_020bea1c((char *) self + 0x2fa8);
    func_020be568((char *) self + 0x2fcc);
}
