/* func_ov143_0229a67c @ 0x0229a67c, 0x7c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern int func_ov143_02299c14(void *, int);
extern void func_ov143_0229a31c(void *);
extern void func_ov143_02299fd0(void *);
extern void func_ov143_02299f6c(void *);
extern void func_ov143_0229a014(void *);
extern void func_ov143_0229a200(void *);
extern void func_ov143_0229a230(void *);

struct FlagsStruct {
    char pad_00[2];
    unsigned short flags;
};
extern struct FlagsStruct data_021fbe40;

void func_ov143_0229a67c(void *p)
{
    if (func_ov002_02208014(p)) {
        func_ov143_0229a31c(p);
        return;
    }
    {
        int tmp = func_ov002_02208008(p);
        if (func_ov143_02299c14(p, tmp)) {
            func_ov143_02299fd0(p);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40.flags;
        if (flags & 1) {
            func_ov143_02299f6c(p);
            return;
        }
        if (flags & 2) {
            func_ov143_0229a014(p);
            func_ov143_0229a200(p);
            return;
        }
        if (flags & 8) {
            func_ov143_0229a014(p);
            func_ov143_0229a230(p);
        }
    }
}
