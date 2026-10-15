/* func_ov126_022a03dc @ 0x022a03dc, 0x10c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229ba44(void *p, int v, int n);
extern int func_ov095_0229bebc(void *p, int v);
extern void func_ov126_022a0168(void *p);
extern int func_ov126_022a027c(void *p, int v);
extern int func_ov126_022a032c(void *p, int v);
extern void func_ov126_022a0110(void *p);
extern void func_ov126_022a0614(void *p);
extern void func_ov126_022a054c(void *p);
extern void func_ov126_022a0ae0(void *p, int v);
extern int func_ov126_022a01dc(void *p, unsigned short v);

int func_ov126_022a03dc(unsigned char *self, int v)
{
    int ret;
    int r6 = 1;

    ret = func_ov095_0229ba44(self + 0x19c, v, 6);
    if (ret != 0) {
        func_ov126_022a0168(self);
        return ret;
    }

    if (func_ov095_0229bebc(self + 0x19c, v) != 0) {
        switch (v) {
            case 0x100:
                func_ov126_022a027c(self, r6);
                break;
            case 0x103:
            case 0x104:
            case 0x105:
                if (func_ov126_022a032c(self, v) == 0) {
                    func_ov126_022a0110(self);
                }
                r6 = 2;
                break;
            case 0x118:
                func_ov126_022a0614(self);
                r6 = 2;
                break;
            case 0x119:
                func_ov126_022a054c(self);
                r6 = 2;
                break;
            case 0x116:
                func_ov126_022a0ae0(self, 0);
                r6 = 3;
                break;
            case 0x117:
                func_ov126_022a0ae0(self, r6);
                r6 = 3;
                break;
            default:
                r6 = 2;
                break;
        }
    } else {
        if (func_ov126_022a01dc(self, (unsigned short) v) == 0) {
            func_ov126_022a0110(self);
        }
    }

    return r6;
}
