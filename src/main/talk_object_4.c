/* talk_object_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020675e0 @ 0x020675e0, 0x68 bytes, Thumb
 * func_020675c0 @ 0x020675c0, 0x20 bytes, Thumb
 * func_02067588 @ 0x02067588, 0x38 bytes, Thumb
 */

typedef struct VT {
    unsigned char pad_00[0xc];
    int (*unk_0C)(void *);
} VT;

typedef struct Obj2 {
    VT *vt;
} Obj2;

typedef struct UnkStruct_020675e0 {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad1[0x38 - 0x14];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[0x50 - 0x3a];
    int unk_50;
} UnkStruct_020675e0;

typedef struct UnkStruct_020675e0_2 {
    unsigned char pad_00[0x680];
    UnkStruct_020675e0 *unk_680;
    unsigned char pad1[0x14a8 - 0x684];
    Obj2 *unk_14A8;
} UnkStruct_020675e0_2;

typedef struct SomeObj SomeObj;

typedef struct SomeVtbl {
    void (*unk_00)();
    void (*unk_04)();
    void (*unk_08)();
    void (*unk_0C)();
    void (*unk_10)(SomeObj *, int);
} SomeVtbl;

struct SomeObj {
    SomeVtbl *vtbl;
};

typedef struct UnkStruct_02067588 {
    char pad_00[0x14A8];
    SomeObj *obj;
    char data[0x9E8];
    unsigned char flag;
} UnkStruct_02067588;

extern UnkStruct_020675e0 *func_020a9034(int, int, int);
extern Obj2 *func_020668d4(Obj2 *);
extern void func_02051648(UnkStruct_020675e0 *);
extern void func_02051694(UnkStruct_020675e0 *);
extern void func_020a8fb8(void *);
extern int func_020a82a0(const char *data);

void func_020675e0(UnkStruct_020675e0_2 *self)
{
    UnkStruct_020675e0 *obj;
    UnkStruct_020675e0 *dst;
    Obj2 *o;
    volatile int pad;
    (void) &pad;
    self->unk_680 = func_020a9034(0x89, 8, 2);
    obj = self->unk_680;
    if (obj != 0) {
        obj->unk_50 = 2;
        self->unk_680->unk_39 = 0xe;
        o = func_020668d4(self->unk_14A8);
        dst = self->unk_680;
        dst->unk_10 = o->vt->unk_0C(o);
        func_02051648(self->unk_680);
        self->unk_680->unk_38 = 2;
        func_02051694(self->unk_680);
    }
}

void func_020675c0(void *param)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) param + 0x680))) != 0) {
        func_020a8fb8(condition_value0);
        *(unsigned int *) ((char *) param + 0x680) = 0;
    }
}

void func_02067588(UnkStruct_02067588 *this)
{
    if (this->flag != 0) {
        int value = func_020a82a0(this->data);
        this->obj->vtbl->unk_10(this->obj, value);
        this->flag = 0;
    }
}
