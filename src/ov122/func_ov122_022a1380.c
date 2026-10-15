/* func_ov122_022a1380 @ 0x022a1380, 0x140 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208054(void *self, int flag);
extern unsigned char *func_ov122_022a0038(void *self);
extern int func_ov095_0229bf48(void *sub);
extern int func_ov002_0220a784(const void *sub, int val);
extern void func_ov122_022a0df8(void *self);
extern int func_ov122_0229efe8(void *self, int val);
extern void func_ov122_022a0dec(void *self);
extern int func_ov095_0229aff0(void *sub);
extern void func_ov095_0229c22c(void *sub, int a, int b, int c);
extern void func_ov122_022a15b8(void *self, int a, int b);
extern int func_ov122_0229fc30(void *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229b3ec(void *sub);
extern int func_ov122_0229f540(void *self);
extern void func_ov002_0220a574(void *sub);
extern void func_ov122_0229f940(void *self);
extern int func_ov122_022a1110(void *self);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;

void func_ov122_022a1380(char *self)
{
    int r6, r7, r4;
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov122_022a0038(self);
        return;
    }

    r6 = 0;
    if (func_ov095_0229bf48(self + 0xc0)) {
        r6 = 1;
    }

    flag = (data_021fbdd8 != 0 && data_021fbddc != 0);
    if (flag != 0) {
        r7 = data_021f6c58;
        r4 = data_021f6c54;

        if (func_ov002_0220a784(self + 0x4698, 9)) {
            func_ov122_022a0df8(self);
            return;
        }

        if (!func_ov122_0229efe8(self, 0x10)) {
            if (func_ov002_0220a784(self + 0x4698, 0)) {
                func_ov122_022a0dec(self);
                return;
            }
        }

        if (func_ov095_0229aff0(self + 0xc0)) {
            func_ov095_0229c22c(self + 0xc0, 9, 6, 1);
            func_ov122_022a15b8(self, 0, 1);
            return;
        }

        if (r4 < 0x48) {
            if (r7 < 0xe0) {
                if (func_ov122_0229fc30(self)) {
                    func_ov002_02208098((void *) (self), 3);
                    func_ov095_0229b3ec(self + 0xc0);
                    func_ov122_022a15b8(self, 1, 1);
                    return;
                }
            } else {
                if (func_ov122_0229f540(self)) {
                    func_ov002_0220a574(self + 0x4010);
                    func_ov002_02208098((void *) (self), 2);
                    func_ov122_0229f940(self);
                    func_ov122_022a15b8(self, 1, 1);
                    return;
                }
            }
        }

        if (r4 >= 0x48) {
            if (r6 == 0) {
                int r = func_ov122_022a1110(self);
                if (r != 0) {
                    if (r == 1) {
                        func_ov002_02208098((void *) (self), 1);
                    }
                }
            }
        }
    }
}
