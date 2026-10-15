/* func_ov109_0229d048 @ 0x0229d048, 0x8c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov109_0229c534(const void *);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(const void *);
extern int func_ov002_02209044(const void *, int, const void *, int);
extern void func_ov109_0229c75c(const void *);
extern void func_ov002_0220a1dc(const void *);
extern unsigned char *func_ov002_02208098(const void *, unsigned char value);
extern int func_ov109_0229c6f8(const void *);
extern unsigned short data_021fbe40[];

void func_ov109_0229d048(void *arg)
{
    int v;
    unsigned short flags;

    if (func_0206f56c() != 0) {
        func_ov109_0229c534(arg);
        return;
    }
    if (func_ov002_02208014(arg) != 0) {
        func_ov109_0229c534(arg);
        return;
    }
    v = func_ov002_02208008(arg);
    if (func_ov002_02209044((char *) arg + 0x22d8, v, (char *) arg + 0x29d8, 0) != 0) {
        func_ov109_0229c75c(arg);
        return;
    }
    flags = data_021fbe40[1];
    if (flags & 1) {
        func_ov002_0220a1dc((char *) arg + 0x2274);
        func_ov002_02208098(arg, 7);
        return;
    }
    if (flags & 2) {
        func_ov109_0229c6f8(arg);
        return;
    }
}
