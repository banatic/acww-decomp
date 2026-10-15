/* func_ov119_0229c008 @ 0x0229c008, 0x88 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229bc30(void *p);
extern int func_ov119_0229b5a8(void *p, int v);
extern void func_ov119_0229b930(void *p);
extern void func_ov119_0229b808(void *p);
extern int func_ov119_0229c608(void *p, int v);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *p);
extern int func_ov090_02299078(int a);
extern int func_ov090_02299098(int a);

struct FlagsStruct {
    unsigned short unk_00;
    unsigned short flags;
};
extern struct FlagsStruct data_021fbe40;

void func_ov119_0229c008(void *p)
{
    if (func_ov002_02208014(p)) {
        func_ov119_0229bc30(p);
        return;
    } else {
        int v = func_ov002_02208008(p);
        if (func_ov119_0229b5a8(p, v)) {
            func_ov119_0229b930(p);
            return;
        } else {
            unsigned short flags = data_021fbe40.flags;
            if (flags & 1) {
                func_ov119_0229b808(p);
                return;
            } else if (flags & 0x100) {
                int r = func_ov090_02299078(6);
                func_ov119_0229c608(p, r);
                return;
            } else if (flags & 0x200) {
                int r = func_ov090_02299098(6);
                func_ov119_0229c608(p, r);
                return;
            }
        }
    }
}
