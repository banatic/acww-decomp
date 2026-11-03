/* caution_window: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020382d4 @ 0x020382d4, 0x8 bytes, Thumb
 * func_020382d0 @ 0x020382d0, 0x2 bytes, Thumb
 * func_020382b8 @ 0x020382b8, 0x18 bytes, Thumb
 * func_0203827c @ 0x0203827c, 0x3c bytes, Thumb
 * func_02038264 @ 0x02038264, 0x18 bytes, Thumb
 * func_0203822c @ 0x0203822c, 0x36 bytes, Thumb
 * func_02038208 @ 0x02038208, 0x24 bytes, Thumb
 * func_020381d8 @ 0x020381d8, 0x30 bytes, Thumb
 * func_020381a4 @ 0x020381a4, 0x34 bytes, Thumb
 * func_020380f4 @ 0x020380f4, 0xb0 bytes, Thumb
 * func_020380c4 @ 0x020380c4, 0x30 bytes, Thumb
 * func_020380a8 @ 0x020380a8, 0x1c bytes, Thumb
 * func_02038078 @ 0x02038078, 0x2e bytes, Thumb
 * func_02037fe8 @ 0x02037fe8, 0x90 bytes, Thumb
 * func_02037fd0 @ 0x02037fd0, 0x16 bytes, Thumb
 * func_02037fa8 @ 0x02037fa8, 0x26 bytes, Thumb
 */

typedef struct UnkStruct_020382b8 UnkStruct_020382b8;

struct UnkStruct_020382b8 {
    unsigned char pad_00[0xbc];
    int unk_BC;
    unsigned char pad_C0[8];
    unsigned char unk_C8;
};

typedef struct {
    unsigned char pad_00[0xC9];
    unsigned char flag;
} UnkStruct_0203827c;

typedef struct {
    unsigned char pad_00[192];
    int unk_C0;
    unsigned char pad_C4[5];
    unsigned char unk_C9;
} UnkStruct_0203822c;

struct UnkStruct_02038208 {
    char pad_00[0xbc];
    int unk_BC;
    char pad_C0[8];
    char unk_C8;
};

struct UnkStruct_020381a4 {
    unsigned char pad_00[0xbc];
    unsigned int unk_BC;
    unsigned int unk_C0;
    unsigned int unk_C4;
    unsigned char unk_C8;
    unsigned char pad_C9[0x17];
    unsigned int unk_E0;
    unsigned int unk_E4;
};

typedef struct {
    char pad_00[0xc0];
    int unk_C0;
    int unk_C4;
    char pad_C8;
    unsigned char unk_C9;
    char pad_CA[26];
    int unk_E4;
} UnkStruct_020380f4;

typedef struct {
    unsigned char pad_00[0xBC];
    int unk_BC;
    unsigned char pad_C0[8];
    unsigned char unk_C8;
} UnkStruct_020380c4;

typedef struct {
    char pad_00[0xbc];
    int unk_BC;
    int unk_C0;
    int unk_C4;
    unsigned char unk_C8;
    char pad_C9[0x17];
    int unk_E0;
    int unk_E4;
} UnkStruct_02038078;

typedef struct {
    char pad_00[0xC0];
    int unk_C0;
    int unk_C4;
} UnkStruct_02037fe8;

typedef struct {
    char pad_00[0xbc];
    int unk_BC;
    int unk_C0;
    char pad_C4[4];
    char unk_C8;
} UnkStruct_02037fd0;

struct UnkStruct_02037fa8 {
    char pad_00[0xC0];
    int unk_C0;
};

extern void func_0203837c(UnkStruct_020382b8 *obj);
extern unsigned int data_020ccf94;
extern unsigned int func_020732d8(unsigned int);
extern void func_020383c4(UnkStruct_0203827c *);
extern void func_0203864c(struct UnkStruct_02038208 *);
extern void *func_020a8bb8(void *, void *);
extern unsigned char data_021c59d0[];
extern unsigned char data_021c5a24[];
extern void func_02038444(void *obj, int a, int b);
extern void func_0203859c(void *obj);
extern void func_02038680(void *obj, int a);
extern void func_02038368(void *arg);
extern void func_02038bfc(void);
extern void func_020508a0(void);
extern void func_020740a0(void);
extern unsigned char data_021c5b38[];
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned short data_021fbe40[];
extern void func_02116a1c(int arg);

void func_02038264(void *param);
void func_02038208(struct UnkStruct_02038208 *p);
void func_020381a4(struct UnkStruct_020381a4 *ptr);
void func_020380c4(UnkStruct_020380c4 *obj);
void func_02038078(UnkStruct_02038078 *p);
void func_02037fd0(UnkStruct_02037fd0 *obj);

void func_020382d4(int p0)
{
    *(int *) ((char *) (((int) (p0) + (188))) + (0)) = 0;
}

void func_020382d0(void *object) {}

void func_020382b8(UnkStruct_020382b8 *arg)
{
    arg->unk_BC = 1;
    arg->unk_C8 = 0;
    func_0203837c(arg);
}

void func_0203827c(UnkStruct_0203827c *this)
{
    if (this->flag) {
        if ((func_020732d8(data_020ccf94) & 0x7C) != 0) {
            func_020383c4(this);
            func_020380c4((UnkStruct_020380c4 *) this);
        } else {
            func_02038264((void *) this);
        }
    }
}

void func_02038264(void *param)
{
    unsigned char *ptr;
    unsigned int *ptr2;
    unsigned int *ptr3;

    ptr2 = (unsigned int *) ((unsigned char *) param + 0xbc);
    *ptr2 = 2;
    ptr3 = (unsigned int *) ((unsigned char *) param + 0xc0);
    *ptr3 = 0x14;
    ptr = (unsigned char *) param + 0xc8;
    *ptr = 0;
}

void func_0203822c(UnkStruct_0203822c *p)
{
    if (p->unk_C9 == 0) {
        func_020382b8((UnkStruct_020382b8 *) p);
    } else {
        p->unk_C0--;
        if (p->unk_C0 <= 0) {
            func_02038208((struct UnkStruct_02038208 *) p);
        }
    }
}

void func_02038208(struct UnkStruct_02038208 *p)
{
    p->unk_BC = 3;
    p->unk_C8 = 0;
    func_0203864c(p);
    func_020383c4((UnkStruct_0203827c *) p);
}

void func_020381d8(void *param0)
{
    void *r4;
    r4 = param0;
    func_020a8bb8((void *) ((unsigned int) r4 + 0xe8), (void *) data_021c5a24);
    func_020a8bb8((void *) ((unsigned int) r4 + 0x1fc), (void *) data_021c59d0);
    func_020381a4((struct UnkStruct_020381a4 *) r4);
}

void func_020381a4(struct UnkStruct_020381a4 *ptr)
{
    ptr->unk_BC = 4;
    ptr->unk_C0 = 0x12c;
    ptr->unk_C4 = 0;
    ptr->unk_C8 = 1;
    ptr->unk_E0 = 0;
    ptr->unk_E4 = 15;
}

void func_020380f4(UnkStruct_020380f4 *obj)
{
    int temp = (obj->unk_C0 + 0x13) / 0x14;
    int changed = (obj->unk_E4 != temp);
    obj->unk_E4 = temp;

    if (obj->unk_C4 < 4) {
        func_02038444(obj, obj->unk_C4, 0);
        func_0203859c(obj);
        func_02038680(obj, obj->unk_C4);
        obj->unk_C4++;
    } else if (changed) {
        func_02038444(obj, 3, 0);
        func_0203859c(obj);
        func_02038680(obj, 3);
    }

    if (obj->unk_C9 == 0) {
        func_020382b8((UnkStruct_020382b8 *) obj);
    } else {
        obj->unk_C0--;
        if (obj->unk_C0 <= -20) {
            func_020380c4((UnkStruct_020380c4 *) obj);
        }
    }
}

void func_020380c4(UnkStruct_020380c4 *obj)
{
    obj->unk_BC = 5;
    obj->unk_C8 = 1;
    func_0203864c((struct UnkStruct_02038208 *) obj);
    func_02038368(obj);
    func_02038bfc();
    func_020508a0();
    func_020740a0();
}

void func_020380a8(void *ptr)
{
    void *r4 = ptr;
    func_020a8bb8((char *) ptr + 0xe8, (void *) ((void *) data_021c5b38));
    func_02038078((UnkStruct_02038078 *) r4);
}

void func_02038078(UnkStruct_02038078 *p)
{
    p->unk_BC = 6;
    p->unk_C4 = 0;
    p->unk_C8 = 1;
    p->unk_E0 = 0;
    p->unk_E4 = -1;
    p->unk_C0 = 0x14;
}

void func_02037fe8(UnkStruct_02037fe8 *param)
{
    if (param->unk_C4 < 4) {
        func_02038444((void *) param, param->unk_C4, 1);
        func_0203859c((void *) param);
        func_02038680((void *) param, param->unk_C4);
        param->unk_C4++;
    }
    param->unk_C0--;
    if (param->unk_C0 <= 0) {
        int cond1 = (data_021fbdd8 != 0) && (data_021fbddc != 0);
        int cond2 = (data_021fbe40[1] & 1) != 0;
        if (cond1 || cond2) {
            func_02037fd0((UnkStruct_02037fd0 *) param);
        }
    }
}

void func_02037fd0(UnkStruct_02037fd0 *obj)
{
    obj->unk_BC = 7;
    obj->unk_C0 = 1;
    obj->unk_C8 = 1;
}

void func_02037fa8(struct UnkStruct_02037fa8 *self)
{
    self->unk_C0 = self->unk_C0 - 1;
    if (self->unk_C0 <= 0) {
        func_02116a1c(0);
    }
}
