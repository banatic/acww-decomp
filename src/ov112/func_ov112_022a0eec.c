/* func_ov112_022a0eec @ 0x022a0eec, 0x60 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;

typedef struct {
    char pad_00[0xbe];
    unsigned char unk_BE;
    unsigned char unk_BF;
} UnkStruct_022a0eec;

extern unsigned char *func_ov002_02208098(UnkStruct_022a0eec *self, unsigned char value);
extern void func_ov112_0229fe50(UnkStruct_022a0eec *self, int val);
extern int func_ov112_0229f730(UnkStruct_022a0eec *self);
extern void func_0200467c(int cmd);
extern void func_ov112_0229fab4(UnkStruct_022a0eec *self);
extern void func_ov112_0229fd20(UnkStruct_022a0eec *self);

void func_ov112_022a0eec(UnkStruct_022a0eec *self)
{
    int result;
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
        if (self->unk_BE == self->unk_BF) {
            func_ov112_0229fe50(self, 0x100);
        }
        result = 1;
    } else {
        result = func_ov112_0229f730(self);
        if (result != 0) {
            func_0200467c(0x15);
        }
    }
    if (result != 0) {
        func_ov112_0229fab4(self);
        func_ov112_0229fd20(self);
    }
}
