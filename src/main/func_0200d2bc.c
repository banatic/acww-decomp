/* func_0200d2bc @ 0x0200d2bc, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02010718(char *);
extern int func_020b67d4(void);
extern unsigned char *func_0209626c(void);
extern int func_02008dc0(unsigned char *, short, int, int);
extern int func_0200d1a0(unsigned char *, unsigned char, int, int);
extern int func_02010538(unsigned char *);
extern int func_0200f748(unsigned char *);
extern int func_020912d4(int, unsigned char *, short *, int);
extern unsigned char data_021c75b8;
extern unsigned char data_ov004_02259a08;

void func_0200d2bc(unsigned char *self)
{
    int r4;
    int r6;

    r6 = func_02010718((char *) self);
    r4 = 0;

    if (func_020b67d4() != 0) {
        unsigned int ok;

        ok = (data_021c75b8 == 2);
        if (ok > 0) {
            if ((*func_0209626c() & 8) == 0) {
                if (data_ov004_02259a08 != 0) {
                    *func_0209626c() |= 8;
                    func_02008dc0(self, *(short *) (self + 0x8e), 6, -1);
                    return;
                }
            }
        }
    }

    if (r6 > 0) {
        unsigned char c;

        c = *(self + 0x7d4);
        if (r6 < 0x53f) {
            c = 0;
        }
        r4 = func_0200d1a0(self, c, 1, -1);
    }

    if (func_02010538(self) == 0) {
        r4 |= func_0200f748(self);
    } else {
        r4 = 1;
    }

    if (r4 != 0) {
        short v;
        short tmp;

        v = *(short *) (self + 0x8e);
        tmp = v + 0xaf0;
        func_020912d4(0x27, self + 0x6d4, &tmp, 0);
        tmp = v - 0xaf0;
        func_020912d4(0x27, self + 0x6c8, &tmp, 0);
    }
}
