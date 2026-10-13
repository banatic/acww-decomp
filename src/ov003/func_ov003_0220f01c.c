/* func_ov003_0220f01c @ 0x0220f01c, 0x10c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *p, int a);
extern void func_02035624(int a);
extern void func_02035ac8(int a);
extern int func_0204e414(void);
extern int func_02073908(int a, int b);
extern int func_0204e108(int a, void *b, int c, int d);
extern int func_0204e08c(int a, void *b, int c, int d);
extern int func_020b5e10(void);
extern void func_020b63f4(int a, int b, void *c, int d, int e, int f, int g);

extern int data_020ccf94;
extern int data_021c526c;

void func_ov003_0220f01c(char *self)
{
    unsigned char *p = (unsigned char *) self + 0x7d4;
    int v6;
    int buf[3];

    if (func_02056f28(self + 0x2d0, 0x2e) != 0) {
        if (p[4] < 2) {
            return;
        }
        func_02035624(0xc);
        func_02035ac8(data_021c526c + 0x2e4);
        return;
    } else {
        if (func_02056f28(self + 0x2d0, 0x2f) == 0) {
            return;
        }
        v6 = func_0204e414();
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
            return;
        }
        if (p[4] == 0) {
            if (func_0204e108(v6, buf, 0, 0) == 0) {
                return;
            }
            {
                int ret = func_020b5e10();
                self += 0x5c;
                func_020b63f4(ret, 0, self, 0x1b800000, 0, 2, 2);
            }
            return;
        } else {
            if (*(int *) (self + 0x800) == 0) {
                if (func_0204e108(v6, buf, 0, 0) == 0) {
                    return;
                }
                buf[2] += 0x2000;
                {
                    int ret = func_020b5e10();
                    func_020b63f4(ret, 0, buf, 0x1b800000, 0, 2, 2);
                }
                return;
            } else {
                if (func_0204e08c(v6, buf, 0, 0) == 0) {
                    return;
                }
                {
                    int ret = func_020b5e10();
                    func_020b63f4(ret, 0, buf, 0x1b800000, 0, 2, 2);
                }
                return;
            }
        }
    }
}
