/* func_ov110_0229dc40 @ 0x0229dc40, 0x80 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov110_0229e7ac(void *receiver);
extern void func_ov110_0229c8f4(char *p);
extern int func_ov002_02208008(char *p);
extern int func_ov002_02209044(char *a, int b, char *c, int d);
extern void func_ov110_0229cb28(char *p);
extern void func_ov002_0220a1dc(char *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov110_0229cac8(char *p);
struct Flags {
    unsigned short unk_00;
    unsigned short unk_02;
};
extern struct Flags data_021fbe40;
void func_ov110_0229dc40(char *p)
{
    int v;
    unsigned short flags;
    if ((func_ov002_02208014(p) != 0) || (func_ov110_0229e7ac(p) != 0)) {
        func_ov110_0229c8f4(p);
        return;
    }
    {
        v = func_ov002_02208008(p);
        if (func_ov002_02209044(p + 0x2344, v, p + 0xfa, 0) != 0) {
            func_ov110_0229cb28(p);
            return;
        }
        flags = data_021fbe40.unk_02;
        if ((flags & 1) != 0) {
            func_ov002_0220a1dc(p + 0x22e0);
            func_ov002_02208098((void *) (p), 7);
            return;
        } else if ((flags & 2) != 0) {
            func_ov110_0229cac8(p);
            return;
        }
    }
}
