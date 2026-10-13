/* func_ov137_0229cb20 @ 0x0229cb20, 0x28 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern void func_ov002_02208098(void *, unsigned char);
extern void func_ov137_0229d0e0(void *);

struct UnkStruct_0229cb20 {
    char pad_00[0x94];
    char unk_94[1];
    char pad_95[0x2b76 - 0x94 - 1];
    unsigned char unk_2B76;
};

void func_ov137_0229cb20(struct UnkStruct_0229cb20 *p)
{
    if (func_ov002_02209f64(&p->unk_94) == 0) {
        func_ov002_02208098(p, p->unk_2B76);
        func_ov137_0229d0e0(p);
    }
}
