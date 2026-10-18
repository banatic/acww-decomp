/* func_ov004_0220d594 @ 0x0220d594, 0x124 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" char *func_ov004_0220db94(void *list);
extern "C" void func_ov004_0220f27c(void *arg, void *list, int a, int b);
extern "C" int func_ov004_0220d6b8(void *self, void *arg);
extern "C" void func_ov004_0220d800(void *self);
extern "C" void func_ov004_0220fc98(void *arg, int a, int b);
extern "C" int MTX_Inverse43(void *a, void *b);
extern "C" int *func_ov004_0220db5c(void *list, unsigned int i);
extern "C" unsigned int func_ov004_0220db68(void *list);
extern "C" void func_ov004_0220db90(void *list);
extern "C" int func_0204f5e0(void *glob, int xh, int yh, int xl, int yl, int k);
extern "C" int func_0204bd08(int r);
extern "C" void func_0204f794(void *item, int x, int y);
extern "C" void MTX_MultVec43(void *item, void *a, void *out);
extern "C" int func_ov004_0220d788(void *self, int r, void *out);
extern "C" unsigned short data_ov004_02256c44;
extern "C" int data_ov004_02256c84;
extern "C" char data_ov004_02256dd4[];
extern "C" void func_020051b0(void *p);
extern "C" void __register_global_object(void *object, void *dtor, void *chain);
extern void *data_021c80bc;
extern char data_021fbe48[];

extern "C" int func_ov004_0220d594(void *self, void *arg)
{
    // a function-local static (id 0xfff1) with an empty destructor, constructed on the
    // first call; nothing reads it
    if ((data_ov004_02256c84 & 1) == 0) {
        data_ov004_02256c44 = 0xfff1;
        __register_global_object(&data_ov004_02256c44, (void *) func_020051b0, data_ov004_02256dd4);
        data_ov004_02256c84 |= 1;
    }
    char list[0x24];
    char item[0xc];
    char out[0x10];
    void *glob;
    int ok = 1;
    unsigned int i;
    int x, y, r, z, xh, yh;

    func_ov004_0220db94(list);
    func_ov004_0220f27c(arg, list, 0, 0);
    glob = data_021c80bc;
    if (func_ov004_0220d6b8(self, arg) != 0) {
        func_ov004_0220d800(self);
        func_ov004_0220fc98(arg, 0, 0);
        MTX_Inverse43(data_021fbe48, data_021fbe48);
        i = 0;
        z = 0;
        for (; i < func_ov004_0220db68(list); i++) {
            x = func_ov004_0220db5c(list, i)[0];
            y = func_ov004_0220db5c(list, i)[1];
            xh = x >> 4;
            yh = y >> 4;
            r = func_0204f5e0(glob, xh, yh, x - (xh << 4), y - (yh << 4), 1);
            if (r != 0 && func_0204bd08(r) != 0) {
                func_0204f794(item, x, y);
                *(int *) (item + 4) = *(int *) ((char *) arg + 0x790);
                MTX_MultVec43(item, data_021fbe48, out);
                ok = ok & func_ov004_0220d788(self, r, out);
                if (ok != 0) {
                    ok = 1;
                } else {
                    ok = z;
                }
            }
        }
        if (ok == 0) {
            func_ov004_0220d800(self);
        }
    }
    func_ov004_0220db90(list);
    return ok;
}
