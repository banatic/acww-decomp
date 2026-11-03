/* pockets_swap_4: 5 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229cf90 @ 0x0229cf90, 0x54 bytes, Thumb
 * func_ov107_0229cf58 @ 0x0229cf58, 0x38 bytes, Thumb
 * func_ov107_0229cf08 @ 0x0229cf08, 0x50 bytes, Thumb
 * func_ov107_0229cec4 @ 0x0229cec4, 0x44 bytes, Thumb
 * func_ov107_0229ceb4 @ 0x0229ceb4, 0x10 bytes, Thumb
 */

typedef struct SomeObj {
    unsigned char pad_before[0xb7];
    unsigned char unk_B7;
    unsigned char unk_B8;
    unsigned char pad_after[0x21cd - 0xb9];
} SomeObj;

struct UnkStruct_ov107 {
    char pad_00[0xa4];
    unsigned int unk_A4;
    unsigned int unk_A8;
    char pad_AC[9];
    unsigned char unk_B5;
    char pad_B6[86];
    char unk_10C;
};

typedef struct {
    char pad_00[0xb8];
    unsigned char byte;
    char pad_B9[0x21fb];
    int unk_22B4;
} UnkStruct_0229cf08;

typedef struct {
    char pad_00[0xb8];
    unsigned char unk_B8;
} UnkStruct_0229cec4;

extern int func_ov107_0229d388(SomeObj *obj, unsigned char val);
extern int func_ov107_0229d128(SomeObj *obj, unsigned char val);
extern void func_ov002_02207cf0(void *addr);
extern void func_ov002_02207cf8(void *addr);
extern int func_ov107_0229c2b4(void *, int);
extern void func_ov094_0229a6bc(void *, unsigned int, unsigned int);
extern void func_ov107_0229ccc8(UnkStruct_0229cf08 *p);
extern void func_ov002_0220a0b4(int *ptr, int a, int b);
extern void func_ov002_0220a374(int *ptr, int arg);
extern int func_ov107_0229d29c(void *p, int c);
extern int func_ov107_0229d260(void *self, unsigned char b);

int func_ov107_0229cec4(UnkStruct_0229cec4 *p);
extern int func_ov107_0229ceb4(void *self);

void func_ov107_0229cf90(SomeObj *obj)
{
    if (func_ov107_0229d388(obj, obj->unk_B8)) {
        if (func_ov107_0229d128(obj, obj->unk_B8)) {
            func_ov002_02207cf0((char *) obj + 0x21cc);
        } else {
            obj->unk_B7 = obj->unk_B8;
            func_ov002_02207cf8((char *) obj + 0x21cc);
        }
    } else {
        func_ov002_02207cf0((char *) obj + 0x21cc);
    }
}

void func_ov107_0229cf58(struct UnkStruct_ov107 *param)
{
    if (func_ov107_0229c2b4(param, 0x20) == 0) {
        if (param->unk_B5 != 0) {
            if (param->unk_B5 == 1) {
                func_ov094_0229a6bc(&param->unk_10C, param->unk_A4, param->unk_A8);
            }
        }
    }
}

void func_ov107_0229cf08(UnkStruct_0229cf08 *p)
{
    int a = func_ov107_0229cec4((UnkStruct_0229cec4 *) p);
    int b = func_ov107_0229ceb4((void *) p);
    func_ov002_0220a0b4(&p->unk_22B4, a, b);
    if (p->byte == 15) {
        func_ov002_0220a374(&p->unk_22B4, 7);
    } else {
        func_ov002_0220a374(&p->unk_22B4, 1);
    }
    func_ov107_0229ccc8(p);
}

int func_ov107_0229cec4(UnkStruct_0229cec4 *p)
{
    int r;
    r = func_ov107_0229d29c(p, p->unk_B8);
    if (func_ov107_0229c2b4(p, 0x10)) {
        r += 0x100;
    } else {
        if (func_ov107_0229c2b4(p, 8)) {
            r -= 0x100;
        }
    }
    r += 8;
    return r;
}

extern int func_ov107_0229ceb4(void *self)
{
    return func_ov107_0229d260(self, ((unsigned char *) self)[0xb8]);
}
