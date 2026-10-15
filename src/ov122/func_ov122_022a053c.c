/* func_ov122_022a053c @ 0x022a053c, 0x94 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov122_0229efd8(void *, int);
extern void func_ov122_0229f0a8(void *);
extern int func_ov002_02208014(void *receiver);
extern void func_ov122_0229ff94(void *);
extern int func_ov002_02208008(void *);
extern int func_ov002_02209044(void *, int, void *, int);
extern void func_ov122_0229f104(void *);
extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned short data_021fbe40[];

void func_ov122_022a053c(void *param)
{
    int tmp;
    unsigned short flags;

    if (func_0206f56c()) {
        func_ov122_0229efd8(param, 0x2000);
        func_ov122_0229f0a8(param);
        return;
    }
    if (func_ov002_02208014(param)) {
        func_ov122_0229ff94(param);
        return;
    }
    tmp = func_ov002_02208008(param);
    if (func_ov002_02209044((char *) param + 0x42b0, tmp, (char *) param + 0xb6, 0)) {
        func_ov122_0229f104(param);
    }

    flags = data_021fbe40[1];
    if (flags & 1) {
        func_ov002_0220a1dc((char *) param + 0x4058);
        func_ov002_02208098((void *) (param), 0x15);
    } else if (flags & 2) {
        func_ov122_0229f0a8(param);
    }
}
