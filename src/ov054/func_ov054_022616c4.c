/* func_ov054_022616c4 @ 0x022616c4, 0x74 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022616c4 {
    char pad_00[0x808];
    int n;
} UnkStruct_022616c4;

typedef struct UnkStruct_022616c4_2 {
    char pad_00[0x40];
    void *obj;
    char pad_44[0x6c];
    UnkStruct_022616c4 *unk_B0;
} UnkStruct_022616c4_2;

extern int func_020a1848(void);
extern int func_020a186c(void);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern void func_0206844c(void *, char *, int);
extern void func_ov054_02261cc4(UnkStruct_022616c4_2 *, int);
extern char data_ov054_02262fac[];

void func_ov054_022616c4(UnkStruct_022616c4_2 *p)
{
    void *obj;
    char c;
    int idx;
    int val;

    obj = p->obj;
    if (func_020a1848() != 0) {
        func_02068358(obj);
        func_02068434(obj);
        c = 2;
        idx = p->unk_B0->n;
        val = *(int *) (data_ov054_02262fac + idx * 12);
        func_0206844c(obj, &c, val);
        func_ov054_02261cc4(p, 0);
    } else if (func_020a186c() != 0) {
        func_02068358(obj);
        func_02068434(obj);
        func_ov054_02261cc4(p, 0);
    }
}
