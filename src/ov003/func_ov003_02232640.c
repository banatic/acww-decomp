/* func_ov003_02232640 @ 0x02232640, 0x234 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern int func_02070070(void);
extern int func_ov003_02219604(void);
extern int func_ov068_02270680(unsigned char *self, short *p);
extern void func_ov068_02270750(unsigned char *self, short *p, int a);
extern void func_02056fcc(char *p, int a, int b, int c, int d);
extern void func_ov003_02233178(unsigned char *self, short *p);
extern void func_ov003_022353a4(unsigned char *self, int a, int b);
extern void func_ov003_02232f78(unsigned char *self, short *p);
extern int func_020e8870(short *t, int a, int b);
extern int func_ov003_02233c70(int a, int b);
extern int func_ov003_02234984(unsigned char *self);
extern int func_020644cc(int n);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

void func_ov003_02232640(unsigned char *self)
{
    int flag;
    char *p;
    short t;
    int state;
    Vec3 *pos;
    short *p23e;
    unsigned v;
    int n;
    int h;

    flag = 0;
    state = self[0x251];
    pos = (Vec3 *) (self + 0x204);
    p23e = (short *) (self + 0x23e);
    p = (char *) self;
    p = (char *) ((int) p + 0x50);
    if (func_02070070() == 0) {
        if (func_ov003_02219604() != 0) {
            self[0x247] = 1;
        } else {
            self[0x247] = 0;
        }
    }
    if (self[0x24c] == 0 && state != 0xb && state != 9) {
        flag = func_ov068_02270680(self, (short *) (self + 0x236));
        if (self[0x251] != 5) {
            if (flag == 1) {
                return;
            }
            if (*(signed char *) (self + 0x24d) == 0x37 && flag == 0) {
                v = (unsigned) (*(int *) ((int) p + 0xa4) << 4) >> 16;
                if (v > 3) {
                    p = (char *) ((int) p + 0x9c);
                    func_02056fcc(p, 3, 3, 0x1000, v);
                } else if (v == 3) {
                    p = (char *) ((int) p + 0x9c);
                    func_02056fcc(p, 3, 0, 0x1000, 0);
                }
            }
        }
    }
    switch (state) {
        case 4:
        case 5:
        case 7:
            func_ov068_02270750(self, (short *) (self + 0x23e), flag);
            break;
        case 11:
            func_ov003_02233178(self, (short *) (self + 0x242));
            break;
        case 9:
            func_ov003_022353a4(self, 0, 1);
            func_ov003_02232f78(self, (short *) (self + 0x242));
            break;
        case 3:
            t = *(short *) (self + 0x23a);
            if (func_020e8870(&t, *(short *) (self + 0x240), 0x666) != 0) {
                self[0x251] = 4;
            }
            *(short *) (self + 0x23a) = t;
            break;
        case 0x13:
            if (self[0x24c] != 0) {
                n = *p23e;
                if (n == 0 || *(signed char *) (self + 0x24d) == 0x37) {
                    self[0x251] = 3;
                    *(short *) (self + 0x244) = 0x64;
                    h = *(short *) (self + 0x23a);
                    n = func_ov003_02233c70(8, 1);
                    *(short *) (self + 0x240) = (short) (n + h + 0x8000);
                    *p23e = 0;
                } else if (pos->y > 0 && *(signed char *) (self + 0x24d) == 0x36) {
                    pos->y = pos->y + (FX_MulFunc(FX_Div(0x1000, 0x12000), n << 12) + -10 * (n * n));
                    *p23e = (short) (*p23e + 3);
                    if (pos->y <= 0) {
                        *p23e = 0;
                    }
                }
            } else if (func_ov003_02234984(self) != 0) {
                self[0x251] = 3;
                *(short *) (self + 0x244) = (short) (0x14 * func_020644cc(3));
                h = *(short *) (self + 0x23a);
                n = func_ov003_02233c70(0x10, 1);
                *(short *) (self + 0x240) = (short) (n + h);
            }
            break;
    }
}
