/* func_ov003_0221c8fc @ 0x0221c8fc, 0x19c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00[0x198 - 0x0];
    int unk_198;
    unsigned char pad_19C[0x2b4 - 0x19c];
    unsigned char unk_2B4;
    unsigned char unk_2B5;
    unsigned char unk_2B6;
    unsigned char pad_2B7;
    unsigned char unk_2B8[0x2d8 - 0x2b8];
    unsigned char unk_2D8;
    unsigned char unk_2D9;
} UnkStruct_0221c8fc;

extern void func_0209e474(int *p);
extern void func_0203efb0(UnkStruct_0221c8fc *self, int idx);
extern int func_0205650c(void *p, int a, int b);
extern int func_ov009_02264cf8(UnkStruct_0221c8fc *self, int a);
extern void func_02056478(void *p, int a, int b, int c, int d);
extern int func_02055e00(void *p);
extern void func_020563dc(void *p, int a);
extern void func_ov003_0221c724(UnkStruct_0221c8fc *self);

extern unsigned char data_ov003_0223c8b0;
extern int data_021c9b1c;

extern unsigned int data_ov003_0223c8b8;
extern unsigned int data_ov003_0223c8c0;
extern unsigned int data_ov003_0223c8bc;

int func_ov003_0221c8fc(UnkStruct_0221c8fc *self)
{
    int local[3];

    self->unk_2B4 = data_ov003_0223c8b0;
    self->unk_2B5 = 0;
    func_0203efb0(self, self->unk_2B4);

    if (func_0205650c(self->unk_2B8, self->unk_198, data_021c9b1c) != 0) {
        func_02056478(self->unk_2B8, func_ov009_02264cf8(self, 0), 1, 0x1000, 0);
        func_020563dc(self->unk_2B8, func_02055e00(self->unk_00 + 0x13c));
    }

    self->unk_2D8 = 1;
    self->unk_2B6 = 0xff;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (((unsigned char *) local)[4] == 1) {
        goto end;
    }

    switch (self->unk_2B4) {
        case 0:
            self->unk_2B6 = (unsigned char) ((data_ov003_0223c8b8 / 10) & 1);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 1:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8b8 % 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 2:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8c0 / 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 3:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8c0 % 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 0;
            break;
        case 4:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8bc / 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 1;
            break;
        case 5:
            self->unk_2B6 = (unsigned char) (data_ov003_0223c8bc % 10);
            self->unk_2B5 = self->unk_2B6;
            self->unk_2D9 = 1;
            break;
    }

end:
    func_ov003_0221c724(self);
    return 1;
}
