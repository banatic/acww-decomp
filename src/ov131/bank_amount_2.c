/* bank_amount_2: 2 functions, module ov131
 * mwccarm 1.2/base -O4,s
 * func_ov131_0229af74 @ 0x0229af74, 0x48 bytes, Thumb
 * func_ov131_0229af40 @ 0x0229af40, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x94 - 0x8d - 1];
    unsigned char unk_94;
    unsigned char pad_95[0x1556 - 0x94 - 1];
    unsigned char unk_1556;
} UnkStruct_0229af40;

extern int func_ov131_0229afe8(void *);
extern int func_ov131_0229afd8(void *);
extern int func_ov130_0229a124(void *);
extern void func_ov002_0220a314(void *);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov131_0229af40(UnkStruct_0229af40 *obj, int a, int b);

void func_ov131_0229af74(void *r0)
{
    int r4;
    int r5;
    int r2;
    int r0_2;

    r4 = (int) r0;
    if (func_ov130_0229a124((void *) (r4 + 0x2c4)) != 0) {
        func_ov002_0220a314((void *) (r4 + 0x94));
    } else {
        func_ov002_0220a2b4((void *) (r4 + 0x94));
    }
    r5 = func_ov131_0229afe8((void *) r4);
    r2 = func_ov131_0229afd8((void *) r4);
    func_ov131_0229af40((UnkStruct_0229af40 *) ((void *) r4), r5, r2);
}

void func_ov131_0229af40(UnkStruct_0229af40 *obj, int a, int b)
{
    func_ov002_0220a05c(&obj->unk_94, a, b, 3, 1);
    obj->unk_1556 = obj->unk_8D;
    func_ov002_02208098((void *) (obj), 3);
}
