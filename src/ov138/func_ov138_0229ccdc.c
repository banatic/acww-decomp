/* func_ov138_0229ccdc @ 0x0229ccdc, 0x7c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void);
extern void *func_ov002_02208008(void *p);
extern int func_ov138_0229c9fc(void *p);
extern int func_ov138_0229c588(void *p, void *x);
extern void func_ov138_0229c6e8(void *p);
extern void func_ov138_0229c654(void *p);
extern int func_ov138_0229c738(void *p);
extern void func_ov138_0229c978(void *p);
extern void func_ov138_0229c950(void *p);

struct FlagsStruct {
    unsigned char pad_00[2];
    unsigned short flags;
};

extern struct FlagsStruct data_021fbe40;

void func_ov138_0229ccdc(void *p)
{
    unsigned short flags;

    if (func_ov002_02208014()) {
        func_ov138_0229c9fc(p);
        return;
    }
    if (func_ov138_0229c588(p, func_ov002_02208008(p))) {
        func_ov138_0229c6e8(p);
        return;
    }
    flags = data_021fbe40.flags;
    if ((flags & 1) != 0) {
        func_ov138_0229c654(p);
        return;
    }
    if ((flags & 8) != 0) {
        func_ov138_0229c738(p);
        func_ov138_0229c978(p);
        return;
    }
    if ((flags & 2) != 0) {
        func_ov138_0229c738(p);
        func_ov138_0229c950(p);
    }
}
