/* func_ov137_0229cc80 @ 0x0229cc80, 0x64 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[2];
    unsigned short flags;
} SomeGlobal;

extern SomeGlobal data_021fbe40;
extern int func_ov002_02208014(void);
extern int func_ov002_02208008(void *arg);
extern void func_ov137_0229c9b4(void *arg);
extern int func_ov137_0229c58c(void *arg, int value);
extern void func_ov137_0229c6e4(void *arg);
extern void func_ov137_0229c650(void *arg);
extern void func_ov137_0229c734(void *arg);
extern void func_ov137_0229c92c(void *arg);

void func_ov137_0229cc80(void *arg)
{
    if (func_ov002_02208014() != 0) {
        func_ov137_0229c9b4(arg);
        return;
    }
    if (func_ov137_0229c58c(arg, func_ov002_02208008(arg)) != 0) {
        func_ov137_0229c6e4(arg);
        return;
    }
    if ((data_021fbe40.flags & 1) != 0) {
        func_ov137_0229c650(arg);
        return;
    }
    if ((data_021fbe40.flags & 8) != 0) {
        func_ov137_0229c734(arg);
        func_ov137_0229c92c(arg);
    }
}
