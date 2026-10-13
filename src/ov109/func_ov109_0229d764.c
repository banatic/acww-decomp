/* func_ov109_0229d764 @ 0x0229d764, 0x50 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f58c(void *p);
extern int func_0206f56c(int);
extern void func_ov109_0229c4cc(void *p);
extern void func_ov109_0229c498(void *p);
extern void func_ov109_0229c29c(void *p, int);
extern void func_ov109_0229d4bc(void *p);
extern void func_ov109_0229d7b4(void *p);
extern void func_ov109_0229d4b4(void *p);

int func_ov109_0229d764(void *self)
{
    if (func_0206f56c(func_0206f58c(self)) != 0) {
        unsigned char b = ((unsigned char *) self)[0x8d];
        if (b == 0 || b == 1 || b == 5) {
            func_ov109_0229c4cc(self);
            func_ov109_0229c498(self);
            func_ov109_0229c29c(self, 0x40);
        }
    }
    func_ov109_0229d4bc(self);
    func_ov109_0229d7b4(self);
    func_ov109_0229d4b4(self);
    return 1;
}
