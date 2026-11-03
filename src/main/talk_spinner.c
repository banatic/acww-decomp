/* talk_spinner: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208fc04 @ 0x0208fc04, 0x8 bytes, Thumb
 * func_0208fc00 @ 0x0208fc00, 0x2 bytes, Thumb
 * func_0208fbf0 @ 0x0208fbf0, 0x10 bytes, Thumb
 * func_0208fbe0 @ 0x0208fbe0, 0x10 bytes, Thumb
 * func_0208fbd8 @ 0x0208fbd8, 0x6 bytes, Thumb
 * func_0208fbd0 @ 0x0208fbd0, 0x6 bytes, Thumb
 * func_0208fbbc @ 0x0208fbbc, 0x14 bytes, Thumb
 * func_0208fb98 @ 0x0208fb98, 0x24 bytes, Thumb
 * func_0208fb70 @ 0x0208fb70, 0x26 bytes, Thumb
 * func_0208fb54 @ 0x0208fb54, 0x1c bytes, Thumb
 * func_0208fb24 @ 0x0208fb24, 0x30 bytes, Thumb
 */

typedef int (*vfunc_t)(void *);

struct VTable {
    vfunc_t vfuncs[4];
};

typedef struct Object Object;

typedef struct VTable_0208fbe0 {
    int (*func0)(Object *);
    int (*func4)(Object *);
    int (*func8)(Object *);
} VTable_0208fbe0;

struct Object {
    VTable_0208fbe0 *vtable;
};

typedef struct {
    unsigned char pad_00[12];
    unsigned long unk_0C;
} UnkStruct_0208fbd0;

struct UnkStruct_0208fbbc {
    char pad_00[0x13];
    unsigned char unk_13;
};

struct UnkStruct_0208fb70 {
    unsigned char pad_00[0x12];
    unsigned char unk_12;
    unsigned char unk_13;
};

typedef struct {
    unsigned char pad_00[0x1c];
    int unk_1C;
    unsigned char unk_20;
} UnkStruct_0208fb54;

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned int index_1c;
    unsigned char flag_20;
} Func0208fb24Struct;

extern void func_02001cf4(int param1);
extern void func_02001bb4(int param1);
extern void func_02001ba4(int);
extern unsigned short data_020d0bac[];
extern void func_02004658(int value);
extern void func_02004644(int a, int b);

void func_0208fbd0(UnkStruct_0208fbd0 *p);
void func_0208fb98(void *param1);
void func_0208fb54(UnkStruct_0208fb54 *param);
void func_0208fb24(Func0208fb24Struct *obj);

void func_0208fc04(void *argument0)
{
    func_0208fbd0((UnkStruct_0208fbd0 *) ((void *) argument0));
}

void func_0208fc00(void *object) {}

int func_0208fbf0(void *obj)
{
    struct VTable *vt;
    vt = *(struct VTable **) obj;
    return vt->vfuncs[3](obj);
}

int func_0208fbe0(Object *self)
{
    return self->vtable->func8(self);
}

void func_0208fbd8(int *p, int a, int b)
{
    p[5] = a;
    p[6] = b;
}

void func_0208fbd0(UnkStruct_0208fbd0 *p)
{
    p->unk_0C = 0;
}

void func_0208fbbc(struct UnkStruct_0208fbbc *p)
{
    if (p->unk_13) {
        func_0208fb98((void *) p);
    }
}

void func_0208fb98(void *param1)
{
    unsigned char temp;

    *(int *) ((char *) param1 + 0xc) = 1;
    func_0208fb54((UnkStruct_0208fb54 *) param1);
    temp = *(unsigned char *) ((char *) param1 + 0x12);
    if (temp != 0) {
        func_02001cf4(0x10);
        func_02001bb4(4);
    }
}

void func_0208fb70(struct UnkStruct_0208fb70 *p)
{
    if (p->unk_13 != 0) {
        return;
    }
    func_0208fb24((Func0208fb24Struct *) p);
    if (p->unk_12 != 0) {
        func_02001ba4(4);
    }
    func_0208fbd0((UnkStruct_0208fbd0 *) p);
}

void func_0208fb54(UnkStruct_0208fb54 *param)
{
    int index = param->unk_1C;
    unsigned short value = data_020d0bac[index];
    param->unk_20 = 1;
    func_02004658(value);
}

void func_0208fb24(Func0208fb24Struct *obj)
{
    unsigned short val = data_020d0bac[obj->index_1c];
    if (obj->flag_20) {
        obj->flag_20 = 0;
        func_02004644(val, 1);
    }
}
