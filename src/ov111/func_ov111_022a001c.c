/* func_ov111_022a001c @ 0x022a001c, 0xd8 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

extern int func_0206fe60(void);
extern int func_0206fe54(void);
extern int func_ov095_0229afac(const void *ptr);
extern void func_ov002_0220a164(const void *ptr);
extern void func_ov002_02208098(void *self, int value);
extern int func_0208e4bc(const void *ptr);
extern void func_ov111_0229fcb0(void *self);
extern void func_ov111_0229f994(void *self);
extern void func_ov111_0229fd08(void *self);
extern void func_ov111_0229fed8(void *self, unsigned char val);
extern void func_ov111_022a0198(void *self);
extern void func_ov111_022a01dc(void *self);

void func_ov111_022a001c(unsigned char *self)
{
    if (func_0206fe60()) {
        unsigned int flag = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        if (flag > 0) {
            if (self[0xa2] == 0 && func_ov095_0229afac(self + 0xac) != 0) {
                func_ov111_022a0198(self);
            }
        }
    }
    if (self[0x9a] != 0) {
        if (self[0x9a] == 3) {
            func_ov111_0229fcb0(self);
        }
        self[0x9a] = self[0x9a] - 1;
        func_ov111_0229fed8(self, self[0x9a]);
        if (self[0x9a] == 1) {
            if (func_0206fe54()) {
                func_ov002_0220a164(self + 0x3d38);
            }
        }
    } else {
        func_ov111_0229f994(self);
        func_ov111_0229fd08(self);
        if (func_0206fe60()) {
            func_ov002_02208098(self, 0);
        } else if (func_0208e4bc(self + 0x3d38)) {
            func_ov002_02208098(self, 7);
        } else {
            func_ov111_022a01dc(self);
        }
    }
}
