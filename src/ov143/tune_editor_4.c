/* tune_editor_4: 3 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_0229a134 @ 0x0229a134, 0x36 bytes, Thumb
 * func_ov143_0229a0b0 @ 0x0229a0b0, 0x84 bytes, Thumb
 * func_ov143_0229a030 @ 0x0229a030, 0x80 bytes, Thumb
 */

extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov002_0220a374(void *addr, int val);
extern void func_ov143_02299f84(void *self);
extern int func_ov002_0220a768(void *, int);
extern void func_ov143_022996a4(void *, int *, int _x);
extern int func_ov002_0220a72c(void *self, int param);

int func_ov143_0229a0b0(unsigned char *self);
int func_ov143_0229a030(void *self);

void func_ov143_0229a134(void *self)
{
    int a;
    int b;

    a = func_ov143_0229a0b0((unsigned char *) self);
    b = func_ov143_0229a030(self);
    func_ov002_0220a0b4((char *) self + 0xac, a, b);
    func_ov002_0220a374((char *) self + 0xac, 1);
    func_ov143_02299f84(self);
}

int func_ov143_0229a0b0(unsigned char *self)
{
    unsigned char mode = self[0xa4];

    if (mode <= 0xf) {
        int out[3];
        func_ov143_022996a4(self, out, mode);
        return out[0] + 0xa;
    } else {
        switch (mode) {
            case 0x10:
                return 0x2e;
            case 0x11:
                return 0x94;
            case 0x12:
                return func_ov002_0220a768(self + 0x110, 1) - 6;
            case 0x13:
                return func_ov002_0220a768(self + 0x110, 2) - 6;
            case 0x14:
                return func_ov002_0220a768(self + 0x110, 3);
            case 0x15:
                return func_ov002_0220a768(self + 0x110, 4);
            default:
                return 0x80;
        }
    }
}

int func_ov143_0229a030(void *self)
{
    unsigned char b;
    int local[3];

    b = *(unsigned char *) ((char *) self + 0xa4);
    if (b <= 15) {
        func_ov143_022996a4(self, local, (unsigned char) b);
        return local[1] + 3;
    }
    switch (b) {
        case 16:
            return 0xa0;
        case 17:
            return 0xa0;
        case 18:
            return func_ov002_0220a72c((char *) self + 0x110, 1);
        case 19:
            return func_ov002_0220a72c((char *) self + 0x110, 2);
        case 20:
            return func_ov002_0220a72c((char *) self + 0x110, 3);
        case 21:
            return func_ov002_0220a72c((char *) self + 0x110, 4);
        default:
            return 0x60;
    }
}
