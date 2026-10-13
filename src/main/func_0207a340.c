/* func_0207a340 @ 0x0207a340, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_02079350(void);
extern int func_020951bc(int);
extern int func_0207a404(void);
extern int func_0208150c(const void *self);
extern int func_02003704(int);
extern int func_020807a8(const void *self, int a);
extern int func_0207f1d8(const void *self);
extern int func_020644cc(int n);

void func_0207a340(const char *self, int a)
{
    unsigned char mask;
    int count;
    int i;
    int sel;
    int thr;

    func_02079350()[0x160] = -1;

    if (a == 0) {
        return;
    }
    if (func_020951bc(a) == 0) {
        return;
    }

    thr = func_0207a404();

    mask = 0;
    count = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(self)) != 0 && func_020807a8(self, a) != 0 && func_0207f1d8(self) == 0) {
            mask |= (1 << i);
            count++;
        }
        self += 0x7ec;
    }

    while (count > 0) {
        sel = func_020644cc(count);
        count--;
        for (i = 0; i < 8; i++) {
            if (((mask >> i) & 1) != 0) {
                if (sel == 0) {
                    if (func_020644cc(100) < thr) {
                        func_02079350()[0x160] = i;
                        count = 0;
                    }
                    mask &= ~(1 << i);
                    break;
                }
                sel--;
            }
        }
    }
}
