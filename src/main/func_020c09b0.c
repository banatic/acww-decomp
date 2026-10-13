/* func_020c09b0 @ 0x020c09b0, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bf514(void *, int, int, int);
extern int func_020bf308(void *, int, int, int);
extern void func_020bee60(void *, int);
extern void func_020beb78(int, int);
extern void func_020bf26c(void *, int);
extern void func_020bf248(void *, int);
extern void func_020bf5b8(void *);
extern void func_020beb64(int);
extern void func_020beb00(int, int, int, int, int);
extern int FX_MulFunc(int, int);
extern void VEC_Add(void *, void *, void *);

typedef struct {
    char pad_00[0x04];
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[0x24 - 0x10];
    int unk_24;
    char pad_28[0x2e - 0x28];
    unsigned char unk_2E;
    char pad_2F[0x34 - 0x2f];
    int unk_34;
    int unk_38;
    char pad_3C[0x40 - 0x3c];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    char pad_50[0x60 - 0x50];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c09b0;

typedef struct {
    char pad_00[12];
} Elem12;
extern Elem12 data_021fa678[];

extern unsigned char data_021fbaf0[];

void func_020c09b0(UnkStruct_020c09b0 *self)
{
    int flag;

    if (self->unk_60 == 0) {
        if (func_020bf514(self, 0x1ec, 0x5000, 0x3e8)) {
            self->unk_04 = 3;
        } else {
            if (func_020bf308(self, 0xe000, 0x1a000, (int) 0xffffd000)) {
                int cnt = self->unk_08 + 1;
                func_020bee60(&data_021fa678[self->unk_24], cnt);
                self->unk_08 = cnt;
                func_020beb78((unsigned int) data_021fbaf0, self->unk_64 != 0 ? 1 : 0);
                func_020bf26c(self, 0x7f8);
                self->unk_60 = 1;
            } else {
                func_020bf248(self, 0x7f7);
            }
        }
    } else if (self->unk_60 == 1) {
        self->unk_0C = 0;
        func_020bf5b8(self);
        self->unk_40 = 0;
        self->unk_44 = (int) 0xfffff800;
        self->unk_48 = 0;
        self->unk_60 = 2;
        self->unk_68 = 0;
    } else {
        self->unk_44 += 0x666;
        self->unk_44 = FX_MulFunc(self->unk_44, 0xfd7);
        VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
        if (self->unk_38 > 0xd0000) {
            func_020beb64((unsigned int) data_021fbaf0);
            self->unk_04 = 3;
        }
    }

    if (self->unk_60 >= 1) {
        flag = (self->unk_2E == 0) ? 1 : 0;
        func_020beb00((unsigned int) data_021fbaf0, self->unk_34, self->unk_38, self->unk_4C, flag);
    }
}
