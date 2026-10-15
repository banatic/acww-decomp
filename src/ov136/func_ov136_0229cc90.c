/* func_ov136_0229cc90 @ 0x0229cc90, 0x64 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov136_0229c9b0(void *arg);
extern void func_ov136_0229c6e4(void *arg);
extern void func_ov136_0229c650(void *arg);
extern void func_ov136_0229c734(void *arg);
extern void func_ov136_0229c92c(void *arg);
extern int func_ov136_0229c58c(void *arg, int v);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *arg);

struct _FlagsStruct {
    unsigned short pad_00;
    unsigned short flags;
};
extern struct _FlagsStruct data_021fbe40;

void func_ov136_0229cc90(void *param)
{
    int v;
    unsigned short flags;

    if (func_ov002_02208014(param)) {
        func_ov136_0229c9b0(param);
        return;
    }

    v = func_ov002_02208008(param);
    if (func_ov136_0229c58c(param, v)) {
        func_ov136_0229c6e4(param);
        return;
    }

    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov136_0229c650(param);
        return;
    }

    if (flags & 8) {
        func_ov136_0229c734(param);
        func_ov136_0229c92c(param);
    }
}
