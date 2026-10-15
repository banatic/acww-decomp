/* func_ov145_0229a4e4 @ 0x0229a4e4, 0x64 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void *func_ov002_02208008(void *arg);
extern int func_ov145_022997d0(void *arg, void *arg2);
extern void func_ov145_02299e90(void *arg);
extern void func_ov145_0229a358(void *arg);
extern void func_ov145_02299e2c(void *arg);
extern void func_ov145_02299ed0(void *arg);
extern void func_ov145_0229a2e0(void *arg);

struct Global021fbe40 {
    unsigned char pad_00[2];
    unsigned short flags;
};
extern struct Global021fbe40 data_021fbe40;

void func_ov145_0229a4e4(void *arg)
{
    unsigned short flags;

    if (func_ov002_02208014(arg)) {
        func_ov145_0229a358(arg);
        return;
    }
    if (func_ov145_022997d0(arg, func_ov002_02208008(arg))) {
        func_ov145_02299e90(arg);
        return;
    }
    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov145_02299e2c(arg);
        return;
    }
    if (flags & 2) {
        func_ov145_02299ed0(arg);
        func_ov145_0229a2e0(arg);
    }
}
