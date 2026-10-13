/* func_02050cb4 @ 0x02050cb4, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dcf28;
extern char data_021c8230;
extern void *func_02137550(void *, int);

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    void *unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char unk_3A;
    unsigned char unk_3B;
    unsigned char unk_3C;
    unsigned char unk_3D;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned char unk_54;
    unsigned char unk_55;
    unsigned char unk_56;
    unsigned char unk_57;
    int unk_58;
    int unk_5C;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    unsigned char unk_74;
    unsigned char unk_75;
    int unk_78;
} UnkStruct_02050cb4;

typedef struct {
    int x;
    int y;
} Pair;

UnkStruct_02050cb4 *func_02050cb4(UnkStruct_02050cb4 *self, int p1, int p2, int p3)
{
    int local[2];
    int *src;

    self->unk_00 = &data_020dcf28;
    self->unk_04 = 0;

    src = func_02137550(local, 8);
    *(Pair *) &self->unk_08 = *(Pair *) src;

    self->unk_10 = 0;
    self->unk_18 = -1;
    self->unk_1C = p1;
    self->unk_20 = p2;
    self->unk_24 = p3;
    self->unk_28 = &data_021c8230;
    self->unk_2C = 5;
    self->unk_30 = 0;
    self->unk_34 = 1;

    self->unk_38 = 1;
    self->unk_39 = 0xf;
    self->unk_3A = 0;
    self->unk_3B = 0;
    self->unk_3C = 0;
    self->unk_3D = 0;

    self->unk_40 = 0;
    self->unk_44 = 0;
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;

    self->unk_54 = 0;
    self->unk_55 = 0;
    self->unk_56 = 0;
    self->unk_57 = 0;

    self->unk_58 = 0;
    self->unk_5C = -1;
    self->unk_60 = p2 << 5;
    self->unk_64 = -1;
    self->unk_68 = 0;
    self->unk_6C = 0;
    self->unk_70 = 0;

    self->unk_74 = 1;
    self->unk_75 = 0;
    self->unk_78 = 0;

    return self;
}