/* message_query_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7d68 @ 0x020a7d68, 0x44 bytes, Thumb
 * func_020a7d48 @ 0x020a7d48, 0x20 bytes, Thumb
 * func_020a7d20 @ 0x020a7d20, 0x28 bytes, Thumb
 * func_020a7cdc @ 0x020a7cdc, 0x44 bytes, Thumb
 * func_020a7c98 @ 0x020a7c98, 0x44 bytes, Thumb
 * func_020a7c74 @ 0x020a7c74, 0x24 bytes, Thumb
 * func_020a7c38 @ 0x020a7c38, 0x3c bytes, Thumb
 * func_020a7bf4 @ 0x020a7bf4, 0x44 bytes, Thumb
 * func_020a7be0 @ 0x020a7be0, 0x14 bytes, Thumb
 * func_020a7bd0 @ 0x020a7bd0, 0xe bytes, Thumb
 */

typedef struct {
    volatile unsigned int unk_00;
    char pad_04[0x20];
    unsigned int unk_24;
    char unk_28[0x14];
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    unsigned int unk_48;
    unsigned int unk_4C;
    unsigned int unk_50;
    unsigned int unk_54;
    unsigned char unk_58;
} UnkStruct_020a7d68;

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x10];
    int unk_38;
    char pad_3C[0x04];
    int unk_40;
    int unk_44;
} Global1;

typedef struct {
    char pad_00[0x18];
    unsigned char unk_18;
} Global2;

struct UnkStruct_020a7c98 {
    char pad_00[0x18];
    unsigned char unk_18;
    char pad_19[0x24 - 0x19];
    int unk_24;
    char pad_28[0x3c - 0x28];
    int unk_3C;
    char pad_40[0x48 - 0x40];
    int unk_48;
};

struct SomeOtherStruct {
    char pad_00[0x18];
    unsigned char unk_18;
};

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x24];
    int unk_4C;
} UnkStruct_020a7c38;

typedef struct {
    unsigned char pad_00[0x18];
    unsigned char unk_18;
} UnkStruct_020a7c38_2;

typedef struct UnkStruct_020a7bf4 {
    char pad_00[4];
    int unk_04;
    char pad_08[0x1C];
    int unk_24;
    char pad_28[0x28];
    int unk_50;
} UnkStruct_020a7bf4;

typedef struct UnkStruct_020a7bf4_2 {
    char pad_00[0x18];
    unsigned char unk_18;
} UnkStruct_020a7bf4_2;

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x28];
    int unk_50;
    char pad_54[0x4];
    unsigned char unk_58;
} UnkStruct_020a7be0;

extern void *func_020a9484(void *);
extern void func_020a8754(void *);
extern unsigned char data_020e3e44[];
extern unsigned char data_020e3e68[];
extern void *func_020a941c(void *ptr);
extern void func_020edb3c(void *param);
extern void func_020a7a64(void *p);
extern void func_020a9354(void *p, int v);
extern int func_020a92d8(void *p, int v);
extern Global1 data_021f4548;
extern Global2 data_021f4588;

int func_020a7c38(int param);

void *func_020a7d68(UnkStruct_020a7d68 *p)
{
    func_020a9484(p);
    p->unk_00 = (unsigned int) data_020e3e68;
    p->unk_00 = (unsigned int) data_020e3e44;
    p->unk_24 = 0;
    func_020a8754(p->unk_28);
    p->unk_3C = 0;
    p->unk_40 = -1;
    p->unk_44 = -1;
    p->unk_48 = 0;
    p->unk_4C = 0;
    p->unk_50 = 0;
    p->unk_54 = 0;
    p->unk_58 = 0;
    return p;
}

void *func_020a7d48(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) data_020e3e44;
    *(unsigned int *) ptr = (unsigned int) data_020e3e68;
    func_020a941c(ptr);
    return ptr;
}

void *func_020a7d20(void *param)
{
    *(volatile unsigned int *) param = (unsigned int) data_020e3e44;
    *(volatile unsigned int *) param = (unsigned int) data_020e3e68;
    func_020a941c(param);
    func_020edb3c(param);
    return param;
}

int func_020a7cdc(int param1, int param2, int param3)
{
    func_020a7a64(&data_021f4548);

    data_021f4548.unk_24 = 0;
    data_021f4548.unk_40 = param2;
    data_021f4548.unk_44 = param3;

    func_020a9354(&data_021f4548, param1);
    func_020a92d8(&data_021f4548, 0);

    if (data_021f4588.unk_18 != 0) {
        return data_021f4548.unk_38;
    } else {
        return 0;
    }
}

int func_020a7c98(int a, int b)
{
    func_020a7a64(((struct UnkStruct_020a7c98 *) &data_021f4548));
    (*(struct UnkStruct_020a7c98 *) &data_021f4548).unk_24 = 1;
    (*(struct UnkStruct_020a7c98 *) &data_021f4548).unk_48 = b;
    func_020a9354(((struct UnkStruct_020a7c98 *) &data_021f4548), a);
    func_020a92d8(((struct UnkStruct_020a7c98 *) &data_021f4548), 0);
    if ((*(struct SomeOtherStruct *) &data_021f4588).unk_18) {
        return (*(struct UnkStruct_020a7c98 *) &data_021f4548).unk_3C;
    }
    return 0;
}

int func_020a7c74(void *a, int b)
{
    int n;
    int result;

    n = func_020a7c38((int) a) - b - 1;
    result = 0;
    if (n >= 0) {
        result = func_020a7c98((int) a, n);
    }
    return result;
}

int func_020a7c38(int param)
{
    func_020a7a64((void *) (((UnkStruct_020a7c38 *) &data_021f4548)));
    (*(UnkStruct_020a7c38 *) &data_021f4548).unk_24 = 3;
    func_020a9354((void *) (((UnkStruct_020a7c38 *) &data_021f4548)), param);
    func_020a92d8((void *) (((UnkStruct_020a7c38 *) &data_021f4548)), 0);
    if ((*(UnkStruct_020a7c38_2 *) &data_021f4588).unk_18) {
        return (*(UnkStruct_020a7c38 *) &data_021f4548).unk_4C;
    } else {
        return 0;
    }
}

int func_020a7bf4(int a, int b)
{
    func_020a7a64((void *) (((UnkStruct_020a7bf4 *) &data_021f4548)));
    (*(UnkStruct_020a7bf4 *) &data_021f4548).unk_24 = 4;
    (*(UnkStruct_020a7bf4 *) &data_021f4548).unk_50 = b;
    func_020a9354((void *) (((UnkStruct_020a7bf4 *) &data_021f4548)), a);
    func_020a92d8((void *) (((UnkStruct_020a7bf4 *) &data_021f4548)), 0);
    if ((*(UnkStruct_020a7bf4_2 *) &data_021f4588).unk_18 != 0) {
        return (*(UnkStruct_020a7bf4 *) &data_021f4548).unk_04;
    }
    return 0;
}

void func_020a7be0(UnkStruct_020a7be0 *s)
{
    if (s->unk_24 == 4 && s->unk_50 == 0) {
        s->unk_58 = 1;
    }
}

// placeholder, not actually used
void func_020a7bd0(unsigned char *param0)
{
    unsigned char *ptr;
    unsigned char value;

    if (*(unsigned int *) (param0 + 0x24) == 3) {
        ptr = param0 + 0x58;
        value = 1;
        *ptr = value;
    }
}
