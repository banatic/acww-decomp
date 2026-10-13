/* func_ov095_02299a54 @ 0x02299a54, 0x98 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_022999a0(void *, int, int);
extern int func_ov095_022999b0(void *, int);
extern void func_ov095_0229a720(void *, void *);
extern void func_ov095_0229a4d4(void *, void *);
extern void func_ov095_0229a2d8(void *, void *);
extern void func_ov095_0229aa74(void *);
extern int func_ov095_0229cddc(void *, void *);
extern int func_ov095_0229cda4(void *, void *);

typedef struct {
    char pad_00[0x16];
    unsigned char unk_16;
    char pad_17[0x28 - 0x17];
    void *unk_28;
    char pad_2C[0x43 - 0x2C];
    char unk_43;
} UnkStruct_02299a54;

int func_ov095_02299a54(UnkStruct_02299a54 *s, void *p)
{
    void *saved = s->unk_28;

    s->unk_43 = 0;
    func_ov095_022999a0(s, 0x10, 0);

    switch (s->unk_16) {
        case 0:
            break;
        case 1:
            func_ov095_0229a720(s, p);
            break;
        case 2:
            func_ov095_0229a4d4(s, p);
            break;
        case 3:
            break;
        case 4:
            func_ov095_0229a2d8(s, p);
            break;
    }

    if (func_ov095_022999b0(s, 0x10) != 0) {
        return 4;
    }

    if (saved != s->unk_28) {
        func_ov095_0229aa74(s);
        if (func_ov095_0229cddc(s, s->unk_28) != 0) {
            return 2;
        }
        if (func_ov095_0229cda4(s, s->unk_28) != 0) {
            return 3;
        }
        return 1;
    }
    return 0;
}
