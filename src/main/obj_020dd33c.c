/* obj_020dd33c: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02057d58 @ 0x02057d58, 0x38 bytes, Thumb
 * func_02057d34 @ 0x02057d34, 0x24 bytes, Thumb
 * func_02057d0c @ 0x02057d0c, 0x28 bytes, Thumb
 * func_02057cf4 @ 0x02057cf4, 0x18 bytes, Thumb
 * func_02057cb8 @ 0x02057cb8, 0x3c bytes, Thumb
 * func_02057c68 @ 0x02057c68, 0x50 bytes, Thumb
 * func_02057c44 @ 0x02057c44, 0x24 bytes, Thumb
 * func_02057c20 @ 0x02057c20, 0x24 bytes, Thumb
 * func_02057bf0 @ 0x02057bf0, 0x30 bytes, Thumb
 * func_02057bd4 @ 0x02057bd4, 0x1c bytes, Thumb
 * func_02057bb8 @ 0x02057bb8, 0x1c bytes, Thumb
 * func_02057b90 @ 0x02057b90, 0x28 bytes, Thumb
 * func_02057b60 @ 0x02057b60, 0x30 bytes, Thumb
 * func_02057b34 @ 0x02057b34, 0x2c bytes, Thumb
 */

typedef struct GStruct {
    char pad_00[0xbc];
    int unk_BC;
    char pad_C0[0x15];
    unsigned char unk_D5;
} GStruct;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02057c44;

typedef struct {
    char pad_00[0x60];
    UnkStruct_02057c44 sub;
} UnkStruct_02057c44_2;

struct UnkStruct_02057bf0 {
    unsigned char pad_00[0xc8];
    unsigned char unk_C8;
    unsigned char pad_C9[0x10];
    unsigned char unk_D9;
    unsigned char unk_DA;
};

typedef struct {
    char pad_00[0x50];
    unsigned short unk_50;
} UnkStruct_02057bb8;

struct UnkStruct_02057b34 {
    unsigned int unk_00;
    char pad_04[0xdc - 4];
    char unk_DC;
};

extern int func_020599a8(int, int, int, int, int, int, int);
extern int data_021c9350;
extern int func_0205996c(int a, int b, unsigned int);
extern int func_020598dc(void *, int, int);
extern void func_0204fdbc(int);
extern void func_02059ac4(int);
extern int func_020ea990(void *a, void *b);
extern int func_0205989c(void *p);
extern int func_0205992c(int a, int b);
extern int func_0205963c(int, int, int);
extern void func_020f5948(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020dd33c[];

int func_02057d58(int a, int b, int c, int d, int e, int f)
{
    int result = 0;
    if (data_021c9350) {
        result = func_020599a8(data_021c9350, a, b, c, d, e, f);
    }
    return result;
}

int func_02057d34(int param)
{
    int result = 0;
    int val = data_021c9350;
    if (val != 0) {
        result = func_0205996c(val, param, result);
    }
    return result;
}

int func_02057d0c(int a, int b)
{
    int result = 0;
    if ((*(void **) &data_021c9350) != 0) {
        result = func_020598dc((*(void **) &data_021c9350), a, b);
    }
    return result;
}

unsigned char func_02057cf4(void)
{
    if ((*(unsigned char **) &data_021c9350) != 0) {
        return (*(unsigned char **) &data_021c9350)[0x58];
    }
    return 0xc;
}

void func_02057cb8(int arg)
{
    int id;

    if (data_021c9350 != 0 && func_02057d34(arg) == 1) {
        id = *(int *) (data_021c9350 + 0xc4);
        if (id != -1) {
            func_0204fdbc(id);
        }
        func_02059ac4(data_021c9350);
    }
}

int func_02057c68(void *param)
{
    int result = 0;
    if (param != 0) {
        GStruct *p = (*(GStruct **) &data_021c9350);
        if (p != 0) {
            if (func_020ea990((char *) param + 0x5c, (char *) p + 0x60) <= p->unk_BC) {
                result = 1;
            } else {
                if (func_0205989c(p) != 0 && (*(GStruct **) &data_021c9350)->unk_D5 == 0) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

int func_02057c44(UnkStruct_02057c44 *out)
{
    int result = 0;
    if ((*(UnkStruct_02057c44_2 **) &data_021c9350)) {
        UnkStruct_02057c44 *p = &(*(UnkStruct_02057c44_2 **) &data_021c9350)->sub;
        out->a = (*(UnkStruct_02057c44_2 **) &data_021c9350)->sub.a;
        out->b = p->b;
        out->c = p->c;
        result = 1;
    }
    return result;
}

int func_02057c20(int param)
{
    int result = 0;

    if (data_021c9350) {
        result = func_0205992c(data_021c9350, param);
    }

    return result;
}

int func_02057bf0(int param)
{
    int result = 0;
    if ((*(struct UnkStruct_02057bf0 **) &data_021c9350) != 0) {
        if (((*(struct UnkStruct_02057bf0 **) &data_021c9350)->unk_C8 == param &&
             (*(struct UnkStruct_02057bf0 **) &data_021c9350)->unk_D9 == 1) ||
            (*(struct UnkStruct_02057bf0 **) &data_021c9350)->unk_DA == param) {
            result = 1;
        }
    }
    return result;
}

int func_02057bd4(void)
{
    int result;
    unsigned char *ptr;
    unsigned char value;

    result = 0;
    ptr = (*(unsigned char **) &data_021c9350);
    if (ptr != 0) {
        value = ptr[0xc8];
        if (value != 0) {
            result = 1;
        }
    }
    return result;
}

void func_02057bb8(unsigned short *dst)
{
    *dst = 0xfff1;
    if ((*(UnkStruct_02057bb8 **) &data_021c9350) != 0) {
        *dst = (*(UnkStruct_02057bb8 **) &data_021c9350)->unk_50;
    }
}

int func_02057b90(int a, int b)
{
    int result = 0;
    if (data_021c9350) {
        result = func_0205963c(data_021c9350, a, b);
    }
    return result;
}

void *func_02057b60(void *this)
{
    *(void **) this = (void *) data_020dd33c;
    func_020f5948((char *) this + 0xDC);
    *(void **) this = (void *) data_020da13c;
    func_020ee62c(this);
    func_020edf54(this);
    return this;
}

void *func_02057b34(struct UnkStruct_02057b34 *obj)
{
    obj->unk_00 = (unsigned int) data_020dd33c;
    func_020f5948(&obj->unk_DC);
    obj->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return (void *) obj;
}
