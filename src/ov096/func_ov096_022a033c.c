/* func_ov096_022a033c @ 0x022a033c, 0x88 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov096_0229d16c(void *p);
extern int func_ov002_02208014(void *receiver);
extern int func_ov096_0229fb84(void *p);
extern int func_ov002_02208008(void *p);
extern int func_ov002_02209044(unsigned char *p, int a, unsigned char *q, int b);
extern void func_ov096_0229dd44(void *p);
extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

struct GFlag {
    unsigned char pad_00[2];
    unsigned short unk_02;
};
extern struct GFlag data_021fbe40;

void func_ov096_022a033c(unsigned char *p)
{
    if (func_0206f56c()) {
        func_ov096_0229d16c(p);
        return;
    }
    if (func_ov002_02208014(p)) {
        func_ov096_0229fb84(p);
        return;
    }
    if (func_ov002_02209044(p + 0x2564, func_ov002_02208008(p), p + 0xbc, 0)) {
        func_ov096_0229dd44(p);
    }
    {
        unsigned short flags = data_021fbe40.unk_02;
        if ((flags & 1) != 0) {
            func_ov002_0220a1dc(p + 0x2500);
            func_ov002_02208098((void *) (p), 0x1a);
        } else if ((flags & 2) != 0) {
            func_ov096_0229d16c(p);
        }
    }
}
