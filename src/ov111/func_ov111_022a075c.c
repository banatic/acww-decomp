/* func_ov111_022a075c @ 0x022a075c, 0xd0 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

extern int func_ov002_02208054(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov095_0229bf48(void *);
extern int func_ov095_0229aff0(void *);
extern int func_ov095_0229afac(void *);
extern void func_ov111_022a01dc(void *);
extern void func_ov111_0229f090(void *, int);
extern void func_ov111_0229fd08(void *);
extern int func_ov111_0229f6a8(void *);
extern void func_ov111_022a0198(void *);
extern int func_ov111_0229f600(void *);
extern void func_ov111_0229efec(void *);
extern int func_ov111_0229f6d4(void *);

struct UnkStruct_022a075c {
    unsigned char pad_00[0xa2];
    unsigned char unk_A2;
    unsigned char pad_A3[0xac - 0xa3];
    unsigned char unk_AC[0x80];
};

void func_ov111_022a075c(struct UnkStruct_022a075c *self)
{
    unsigned int flag;
    int result;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov111_022a01dc(self);
        return;
    }
    if (func_ov095_0229bf48(&self->unk_AC) != 0) {
        return;
    }
    flag = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (flag > 0) {
        result = func_ov111_0229f6d4(self);
        if (result != 0) {
            if (result == 1) {
                func_ov002_02208098((void *) (self), 1);
                return;
            }
        } else {
            if (func_ov095_0229aff0(&self->unk_AC) != 0) {
                func_ov111_0229f090(self, 9);
                func_ov111_0229fd08(self);
                return;
            }
            if (func_ov111_0229f6a8(self) != 0) {
                func_ov002_02208098((void *) (self), 0xd);
                return;
            }
            if (self->unk_A2 == 0) {
                if (func_ov095_0229afac(&self->unk_AC) != 0) {
                    func_ov111_022a0198(self);
                    func_ov002_02208098((void *) (self), 0);
                    return;
                }
            }
            if (func_ov111_0229f600(self) != 0) {
                func_ov111_0229efec(self);
                func_ov002_02208098((void *) (self), 2);
                return;
            }
        }
    }
}
