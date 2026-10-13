/* func_020594c0 @ 0x020594c0, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c93e4[3];

extern int func_0204fd3c(int);
extern int func_02059cf8(void *a, int b);
extern void func_02059598(int *dst, void *self, int c);
extern void func_020595fc(void *self, int *dst, int *src, int d);
extern void func_02059674(void *self, int a);
extern void VEC_Add(void *a, void *b, void *c);

typedef struct {
    unsigned char pad_00[0x50];
    unsigned short unk_50;
    unsigned char pad_52[0x26];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    unsigned char pad_90[0x0c];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    int unk_A8;
    int unk_AC;
    int unk_B0;
    unsigned char pad_B4[0x18];
    void *unk_CC;
    unsigned char pad_D0[0x04];
    char unk_D4;
    unsigned char pad_D5[0x03];
    char unk_D8;
} StructDef;

void func_020594c0(StructDef *self)
{
    unsigned int flag = 0;
    int local1[3];
    int local2[3];
    unsigned short value;

    self->unk_84 = flag;
    self->unk_88 = flag;
    self->unk_8C = flag;
    self->unk_78 = flag;
    self->unk_7C = flag;
    self->unk_80 = flag;
    self->unk_9C = flag;
    self->unk_A0 = flag;
    self->unk_A4 = flag;

    local1[0] = data_021c93e4[0];
    local1[1] = data_021c93e4[1];
    local1[2] = data_021c93e4[2];

    value = self->unk_50;
    if (value >= 0x12e8 && value <= 0x131f) {
        flag = 1;
    }
    if (flag > 0) {
        int diff = value - 0x12e8;
        int x = func_0204fd3c(diff);
        int y = func_02059cf8(self->unk_CC, x);
        VEC_Add(local1, (void *) y, local1);
    }

    func_02059598(local2, self, 0);
    VEC_Add(local1, local2, local1);
    func_020595fc(self, &self->unk_9C, local1, 0);

    self->unk_A8 = 0;
    self->unk_AC = 0;
    self->unk_B0 = 0;
    self->unk_D8 = 1;
    self->unk_D4 = 0;
    func_02059674(self, 1);
}