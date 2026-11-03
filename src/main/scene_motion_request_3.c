/* scene_motion_request_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02019eb0 @ 0x02019eb0, 0x6c bytes, Thumb
 * func_02019eac @ 0x02019eac, 0x2 bytes, Thumb
 * func_02019ea0 @ 0x02019ea0, 0xc bytes, Thumb
 * func_02019e80 @ 0x02019e80, 0x1e bytes, Thumb
 * func_02019e04 @ 0x02019e04, 0x7c bytes, Thumb
 * func_02019e00 @ 0x02019e00, 0x4 bytes, Thumb
 * func_02019df8 @ 0x02019df8, 0x6 bytes, Thumb
 * func_02019de8 @ 0x02019de8, 0x10 bytes, Thumb
 * func_02019de4 @ 0x02019de4, 0x4 bytes, Thumb
 */

typedef struct UnkStruct_02019eb0 {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char pad_18[0x04];
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned char pad_24[0x2a];
    unsigned short unk_4E;
    unsigned char pad_50[0x32];
    unsigned short unk_82;
    unsigned char pad_84[0x15];
    unsigned char unk_99;
    unsigned char pad_9A[0x02];
    unsigned int unk_9C;
    unsigned short unk_A0;
    unsigned char pad_A2[0x02];
    unsigned int unk_A4;
    unsigned char unk_A8;
    unsigned char unk_A9;
    unsigned char pad_AA[0x02];
    unsigned int unk_AC;
    unsigned int unk_B0;
} UnkStruct_02019eb0;

typedef struct {
    char pad_00[0x28];
    unsigned int unk_28;
} UnkStruct_02019e80;

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

typedef struct {
    unsigned char pad_00[169];
    unsigned char unk_A9;
} UnkStruct_02019df8;

extern void func_02019d78(UnkStruct_02019eb0 *param);
extern void func_02019af0(UnkStruct_02019eb0 *param, int arg);
extern void MI_CpuFill8(int arg0, int arg1, int arg2);
extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern void func_02019d70(void *a, int b, int c);
extern void func_02019d94(void *a, void *b, unsigned int c, unsigned int d);
extern unsigned short data_020c80f8;

UnkStruct_02019eb0 *func_02019eb0(UnkStruct_02019eb0 *param)
{
    param->unk_4E = 0xfff1;
    param->unk_82 = 0xfff1;
    param->unk_1C = 0x16;
    param->unk_20 = 0;
    param->unk_14 = 0;
    func_02019d78(param);
    func_02019af0(param, 1);
    param->unk_99 = 0;
    param->unk_9C = 0;
    param->unk_A0 = 0;
    param->unk_A4 = 0;
    param->unk_A8 = 1;
    param->unk_A9 = 0;
    param->unk_B0 = 5;
    param->unk_AC = -1;
    return param;
}

void func_02019eac(void *object) {}

void func_02019ea0(int arg0)
{
    MI_CpuFill8(arg0, 0, 0x34);
}

void func_02019e80(UnkStruct_02019e80 *a, UnkStruct_02019e80 *b)
{
    MI_CpuCopy8(b, a, 0x34);
    a->unk_28 = b->unk_28;
}

void func_02019e04(UnkStruct_02019e04 *self, void *other, int a3, int a4, unsigned int a5, unsigned int a6, short a7,
                   unsigned int a8, unsigned int a9)
{
    Sub2 *sub;

    sub = &self->sub2;

    func_02019d70(self, a3, a4);
    func_02019ea0((int) sub);

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

    func_02019e80((UnkStruct_02019e80 *) ((char *) self + 0x60), (UnkStruct_02019e80 *) ((char *) self + 0x2c));
    MI_CpuFill8((int) ((char *) self + 4), 0, 15);

    self->unk_18 = 0;
    self->unk_19 = 0;

    func_02019d94(self, other, self->unk_24, self->unk_28);
}

int func_02019e00(int *p0)
{
    return p0[7];
}

unsigned char func_02019df8(UnkStruct_02019df8 *p)
{
    return p->unk_A9;
}

int func_02019de8(void *arg0)
{
    if (*(int *) ((char *) arg0 + 0x94) == 1) {
        return 1;
    }
    return 0;
}

int func_02019de4(int p0)
{
    return ((int) (p0) + (96));
}
