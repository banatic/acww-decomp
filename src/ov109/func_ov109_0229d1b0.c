/* func_ov109_0229d1b0 @ 0x0229d1b0, 0xa8 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(const void *);
extern int func_0206f56c(void);
extern void func_ov109_0229c534(const void *);
extern int func_ov002_02208054(const void *, int);
extern int func_ov002_02208b00(const void *, unsigned char, unsigned char);
extern void func_ov002_02209114(const void *, int, int);
extern void func_ov002_02208098(const void *, int);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov109_0229d1b0(unsigned char *self)
{
    unsigned int flag;
    int idx;
    unsigned char *base;

    if (func_ov002_02208e28(self + 0x22d8) == 0) {
        return;
    }

    if (func_0206f56c() != 0) {
        func_ov109_0229c534(self);
        return;
    }

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov109_0229c534(self);
        return;
    }

    flag = 0;
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        flag = 1;
    }

    if (flag > 0) {
        idx = func_ov002_02208b00(self + 0x22d8, data_021f6c58, data_021f6c54);
        if (idx < 0) {
            return;
        }
        func_ov002_02209114(self + 0x22d8, idx, 1);
        base = self + idx;
        self[0x29d7] = base[0x26c5];
        func_ov002_02208098(self, 0xc);
    }
}
