/* func_020675e0 @ 0x020675e0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern UnkStruct_020675e0 *func_020a9034(int, int, int);
extern Obj2 *func_020668d4(Obj2 *);
extern void func_02051648(UnkStruct_020675e0 *);
extern void func_02051694(UnkStruct_020675e0 *);

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
