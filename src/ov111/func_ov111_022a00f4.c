/* func_ov111_022a00f4 @ 0x022a00f4, 0xa4 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov095_0229afac(unsigned char *ptr);
extern void func_ov111_022a0198(void *self);
extern void func_ov111_0229fed8(void *self, int val);
extern int func_ov095_0229b3ec(unsigned char *ptr);
extern void func_ov002_02208098(void *self, int param);

typedef struct {
    unsigned char pad_00[0x9a];
    unsigned char unk_9A;
    unsigned char pad_9B[2];
    unsigned char unk_9D;
    unsigned char pad_9E[4];
    unsigned char unk_A2;
    unsigned char pad_A3[9];
    unsigned char unk_AC;
} UnkStruct_022a00f4;

void func_ov111_022a00f4(UnkStruct_022a00f4 *self)
{
    if (func_0206fe60() != 0) {
        unsigned int flag = (data_021fbdd8 && data_021fbddc);
        if (flag > 0) {
            if (self->unk_A2 == 0) {
                if (func_ov095_0229afac(&self->unk_AC) != 0) {
                    func_ov111_022a0198(self);
                }
            }
        }
    }

    if (self->unk_9A < 4) {
        self->unk_9A++;
        func_ov111_0229fed8(self, self->unk_9A);
        self->unk_9D = 3;
    } else {
        if (self->unk_9D != 0) {
            self->unk_9D--;
        } else {
            func_ov095_0229b3ec(&self->unk_AC);
            func_ov002_02208098(self, 0xe);
        }
    }
}
