/* func_0207c76c @ 0x0207c76c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207cf80(void *self);
extern int func_0207c818(void *self, unsigned char mask);
extern int func_0207c8c8(void *self, int idx, int flag);
extern void func_02081518(void *dst, unsigned char data, int a, int b, int c);
extern void func_0207ca74(void *dst, unsigned char data);
extern void func_0209e474(void *dst);
extern void func_0207a188(void *dst, void *src);
extern void func_0209df64(void *dst);

void func_0207c76c(void *self)
{
    int local1, local2, i;
    unsigned char mask;

    mask = 0;
    func_0207cf80(self);

    i = 0;
    local1 = 0;
    local2 = 0;

    do {
        unsigned int idx;
        int v;

        idx = func_0207c818(self, mask);
        if (idx >= 6) {
            continue;
        }

        v = func_0207c8c8(self, idx, 1);
        if (v == ~local2) {
            continue;
        }

        func_02081518((char *) self + 0x7ec * i, (unsigned char) v, local1, local1, 1);
        func_0207ca74((char *) self + 0x4060, (unsigned char) v);

        mask = (unsigned char) (mask | (1 << idx));
    } while (++i < 3);

    func_0209e474((char *) self + 0x4050);
    func_0207a188((char *) self + 0x3f7c, self);
    func_0209df64((char *) self + 0x407a);

    *(((signed char *) self) + 0x4076) = -1;
}
