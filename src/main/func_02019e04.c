/* func_02019e04 @ 0x02019e04, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019d70(void *a, int b, int c);
extern void func_02019ea0(void *p);
extern void func_02019e80(void *a, void *b);
extern void func_02019d94(void *a, void *b, unsigned int c, unsigned int d);
extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern unsigned short data_020c80f8;

typedef struct Sub2 {
    unsigned int pad_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int pad_14;
    short unk_18;
    unsigned char pad_1A[2];
    unsigned short unk_1C;
} Sub2;

typedef struct UnkStruct_02019e04 {
    unsigned int pad_00;
    char data[15];
    unsigned char pad_13[5];
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char pad_1A[10];
    unsigned int unk_24;
    unsigned int unk_28;
    Sub2 sub2;
    unsigned char pad_4C[0x14];
} UnkStruct_02019e04;

void func_02019e04(UnkStruct_02019e04 *self, void *other, int a3, int a4, unsigned int a5, unsigned int a6, short a7,
                   unsigned int a8, unsigned int a9)
{
    Sub2 *sub;

    sub = &self->sub2;

    func_02019d70(self, a3, a4);
    func_02019ea0(sub);

    sub->unk_04 = a5;
    sub->unk_08 = a6;

    if (a8 == 0 && a9 == 0) {
        sub->unk_0C = a5;
        sub->unk_10 = a6;
    } else {
        sub->unk_0C = a8;
        sub->unk_10 = a9;
    }

    sub->unk_18 = a7;
    sub->unk_1C = data_020c80f8;

    func_02019e80((char *) self + 0x60, (char *) self + 0x2c);
    MI_CpuFill8((char *) self + 4, 0, 15);

    self->unk_18 = 0;
    self->unk_19 = 0;

    func_02019d94(self, other, self->unk_24, self->unk_28);
}
