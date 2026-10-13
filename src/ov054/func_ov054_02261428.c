/* func_ov054_02261428 @ 0x02261428, 0x68 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a17a8(void *);
extern int func_020a17d0(void);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern void func_0206844c(void *, char *, int);
extern void func_ov054_02261cc4(void *, int);

struct UnkStruct_02261428 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    void *unk_B0;
};

struct UnkStruct_02261428_2 {
    int value;
    char pad_04[8];
};

extern struct UnkStruct_02261428_2 data_ov054_02262fac[];

void func_ov054_02261428(struct UnkStruct_02261428 *p)
{
    void *r4 = p->unk_40;
    if (func_020a17a8(p)) {
        func_ov054_02261cc4(p, 0);
        return;
    }
    if (func_020a17d0()) {
        char local;
        func_02068358(r4);
        func_02068434(r4);
        local = 0x3c;
        {
            int idx = *(int *) ((char *) p->unk_B0 + 0x808);
            func_0206844c(r4, &local, data_ov054_02262fac[idx].value);
        }
        func_ov054_02261cc4(p, 0);
    }
    return;
}
