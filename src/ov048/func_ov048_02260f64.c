/* func_ov048_02260f64 @ 0x02260f64, 0x118 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eba18(void);
extern int func_020ec1e8(void);
extern int func_020eba08(void);
extern void *func_020b5630(void *);
extern void *func_020b5618(void *);
extern int func_020b45d0(void *, int, int, int, int, int);
extern void func_02068404(void *, int, void *);
extern int func_ov048_022609d0(void *);
extern void func_ov048_02260e28(void *, int, int);

int func_ov048_02260f64(void *self, int flag)
{
    char obj1[64];
    char obj2[64];
    int id;

    id = func_020eba18();
    if (id != 0 || flag != 0) {
        if (flag != 0) {
            func_ov048_02260e28(self, func_ov048_022609d0(self), 0);
        } else {
            if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
                int v = func_020eba08();
                int q;
                if (v < 0) {
                    v = -v;
                }
                q = v / 1000;
                func_020b5630(obj1);
                func_020b5630(obj2);
                func_020b45d0(obj1, q, 2, 6, 0, 0);
                func_020b45d0(obj2, v - q * 1000, 3, 6, 0, 0);
                func_02068404(*(void **) ((char *) self + 0x40), 6, obj1);
                func_02068404(*(void **) ((char *) self + 0x40), 7, obj2);
                if (id == 0x400b) {
                    func_ov048_02260e28(self, 0x7d, 0);
                } else if (id == 0x400a) {
                    func_ov048_02260e28(self, 0x78, 0);
                } else if (v == 0x13a1a) {
                    func_ov048_02260e28(self, 0x7a, 0);
                } else {
                    func_ov048_02260e28(self, 0x7e, 0);
                }
                func_020b5618(obj2);
                func_020b5618(obj1);
            } else {
                func_ov048_02260e28(self, func_ov048_022609d0(self), 0);
            }
        }
        return 1;
    }
    return 0;
}
