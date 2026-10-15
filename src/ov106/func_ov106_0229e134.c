/* func_ov106_0229e134 @ 0x0229e134, 0xa4 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov106_0229c418(char *self);
extern int func_0208e4bc(char *ptr);
extern int func_ov002_0220b5ec(char *ptr, int val);
extern int func_ov002_0220b59c(char *ptr, int val);
extern void func_ov002_0220a0b4(char *ptr, int a, int b);
extern void func_ov002_0220a374(char *ptr, int val);
extern int func_ov002_02208014(void *receiver);
extern void func_ov106_0229cc50(char *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a1dc(char *ptr);

struct GlobalFlags {
    unsigned char pad_00[2];
    unsigned short flags;
};
extern struct GlobalFlags data_021fbe40;

void func_ov106_0229e134(char *self)
{
    if (func_0206f56c() != 0) {
        func_ov106_0229c418(self);
        return;
    }
    if (func_0208e4bc(self + 0x22a0) == 0) {
        int v1, v2;
        v1 = func_ov002_0220b5ec(self + 0x2b3c, 1);
        v2 = func_ov002_0220b59c(self + 0x2b3c, 1);
        func_ov002_0220a0b4(self + 0x22a0, v1, v2);
        func_ov002_0220a374(self + 0x22a0, 1);
    }
    if (func_ov002_02208014(self) != 0) {
        func_ov106_0229cc50(self);
        func_ov002_02208098((void *) (self), 5);
        return;
    } else {
        unsigned short flags;
        flags = data_021fbe40.flags;
        if ((flags & 1) != 0 || (flags & 2) != 0) {
            func_ov002_0220a1dc(self + 0x22a0);
            func_ov002_02208098((void *) (self), 10);
        }
    }
}
