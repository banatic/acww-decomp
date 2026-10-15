/* func_ov100_0229dcd8 @ 0x0229dcd8, 0x7c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *p);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov100_0229c940(void *p);
extern void func_ov100_0229cb80(void *p);
extern void func_ov100_0229cb1c(void *p);
extern unsigned short data_021fbe40[];

void func_ov100_0229dcd8(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov100_0229c940(arg);
        return;
    }
    {
        int v = func_ov002_02208008(arg);
        if (func_ov002_02209044((char *) arg + 0x22d8, v, (char *) arg + 0x2926, 0) != 0) {
            func_ov100_0229cb80(arg);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40[1];
        if (flags & 1) {
            func_ov002_0220a1dc((char *) arg + 0x2274);
            func_ov002_02208098((void *) (arg), 7);
            return;
        } else {
            if (flags & 2) {
                func_ov100_0229cb1c(arg);
            }
        }
    }
}
