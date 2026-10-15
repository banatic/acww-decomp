/* func_ov135_0229cca0 @ 0x0229cca0, 0x98 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern int func_ov134_022997dc(void *, int);
extern void func_ov135_0229c8b4(void *);
extern void func_ov135_0229c564(void *, int);
extern int func_ov135_0229c7a8(void *);
extern int func_ov135_0229c754(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov135_0229c6e8(void *);
extern void func_ov135_0229c654(void *);
extern void func_ov135_0229c8cc(void *);
extern unsigned short data_021fbe40[];

void func_ov135_0229cca0(void *arg)
{
    if (func_ov002_02208014(arg) != 0) {
        func_ov135_0229c8b4(arg);
        return;
    }
    switch (func_ov134_022997dc((char *) arg + 0x2c8, func_ov002_02208008(arg))) {
        case 2:
            func_ov135_0229c564(arg, 4);
            goto default_case;
        case 3: {
            int v1 = func_ov135_0229c7a8(arg);
            int v2 = func_ov135_0229c754(arg);
            func_ov002_0220a0b4((char *) arg + 0x98, v1, v2);
            return;
        }
        default:
        default_case:
            func_ov135_0229c6e8(arg);
            return;
        case 0: {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                func_ov135_0229c654(arg);
                return;
            }
            if (flags & 2) {
                func_ov135_0229c8cc(arg);
            }
            return;
        }
    }
}
