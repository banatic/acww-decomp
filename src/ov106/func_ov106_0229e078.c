/* func_ov106_0229e078 @ 0x0229e078, 0x9c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(const void *);
extern int func_ov106_0229c364(const void *, unsigned int);
extern int func_ov002_02209044(const void *, int, const void *, unsigned char);
extern void func_ov106_0229c868(const void *);
extern void func_ov106_0229cb58(const void *);
extern int func_ov106_0229caf4(const void *);
extern void func_ov002_0220a1dc(const void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

struct OV106Flags {
    unsigned short pad_00;
    unsigned short flags;
};
extern struct OV106Flags data_021fbe40;

void func_ov106_0229e078(char *self)
{
    int a;
    unsigned char b;

    if (func_0206f56c() != 0) {
        func_ov106_0229c868(self);
        return;
    }
    if (func_ov002_02208014(self) != 0) {
        func_ov106_0229c868(self);
        return;
    }
    a = func_ov002_02208008(self);
    b = (unsigned char) func_ov106_0229c364(self, 0x10000);
    if (func_ov002_02209044(self + 0x2304, a, self + 0xbd, b) != 0) {
        func_ov106_0229cb58(self);
        return;
    }
    if (data_021fbe40.flags & 1) {
        func_ov002_0220a1dc(self + 0x22a0);
        func_ov002_02208098((void *) (self), 0xc);
        return;
    }
    if (data_021fbe40.flags & 2) {
        func_ov106_0229caf4(self);
        return;
    }
}
