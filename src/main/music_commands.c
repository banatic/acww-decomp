/* music_commands: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02035ff8 @ 0x02035ff8, 0x12 bytes, Thumb
 * func_02035ff4 @ 0x02035ff4, 0x2 bytes, Thumb
 * func_02035fec @ 0x02035fec, 0x8 bytes, Thumb
 * func_02035fe4 @ 0x02035fe4, 0x8 bytes, Thumb
 * func_02035fd8 @ 0x02035fd8, 0xa bytes, Thumb
 * func_02035fc0 @ 0x02035fc0, 0x18 bytes, Thumb
 * func_02035f6c @ 0x02035f6c, 0x54 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
    unsigned short unk_06;
    unsigned char unk_08;
    unsigned int unk_0C;
    unsigned char unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
} UnkStruct_02035fc0;

struct UnkStruct_02035f6c {
    char pad_00[4];
    unsigned char flag4;
    char pad_05;
    unsigned short unk_06;
    unsigned char flag8;
    char pad_09;
    char pad_0A;
    char pad_0B;
    int unk_0C;
    unsigned char flag10;
    char pad_11;
    char pad_12;
    char pad_13;
    int unk_14;
    int unk_18;
};

extern void func_02004260(int arg);
extern void func_02004270(unsigned short arg);
extern void func_02035820(void *addr, unsigned short arg);
extern void func_0200424c(int arg1, int arg2);
extern char *data_021c526c;

void func_02035fc0(UnkStruct_02035fc0 *param);

void *func_02035ff8(void *self, int value)
{
    *(int *) self = value;
    func_02035fc0((UnkStruct_02035fc0 *) self);
    return self;
}

void func_02035ff4(void *receiver) {}

void func_02035fec(char *p, int v)
{
    p[4] = 1;
    *(short *) (p + 6) = (short) v;
}

void func_02035fe4(char *p, int v)
{
    p[8] = 1;
    *(int *) (p + 0xc) = v;
}

void func_02035fd8(char *p, int a, int b)
{
    p[0x10] = 1;
    *(int *) (p + 0x14) = a;
    *(int *) (p + 0x18) = b;
}

void func_02035fc0(UnkStruct_02035fc0 *param)
{
    param->unk_04 = 0;
    param->unk_06 = 0xffff;
    param->unk_08 = 0;
    param->unk_0C = 0;
    param->unk_10 = 0;
    param->unk_14 = 0;
    param->unk_18 = 0;
}

void func_02035f6c(struct UnkStruct_02035f6c *obj)
{
    if (obj->flag8) {
        obj->flag8 = 0;
        func_02004260(obj->unk_0C);
    }
    if (obj->flag4) {
        obj->flag4 = 0;
        func_02004270(obj->unk_06);
        func_02035820(data_021c526c + 0x2f0, obj->unk_06);
    }
    if (obj->flag10) {
        obj->flag10 = 0;
        func_0200424c(obj->unk_14, obj->unk_18);
    }
}
