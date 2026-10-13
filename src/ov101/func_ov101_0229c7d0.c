/* func_ov101_0229c7d0 @ 0x0229c7d0, 0x74 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0xb6 - 0x8d - 1];
    unsigned char unk_B6;
    unsigned char pad_B7[0x229c - 0xb6 - 1];
    unsigned char unk_229C[1];
} UnkStruct_0229c7d0;

extern int func_ov101_0229c2ac(void *, int);
extern int func_ov101_0229c878(UnkStruct_0229c7d0 *);
extern int func_ov101_0229c868(UnkStruct_0229c7d0 *);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a05c(unsigned char *, int, int, int, int);
extern void func_ov101_0229c28c(UnkStruct_0229c7d0 *, int);
extern void func_ov002_02208098(UnkStruct_0229c7d0 *, int);

void func_ov101_0229c7d0(UnkStruct_0229c7d0 *p)
{
    int res1;
    int res2;
    if (func_ov101_0229c2ac(p, 4)) {
        res1 = func_ov101_0229c878(p);
        res2 = func_ov101_0229c868(p);
        func_ov002_0220a0b4(p->unk_229C, res1, res2);
        func_ov101_0229c28c(p, 4);
    } else {
        res1 = func_ov101_0229c878(p);
        res2 = func_ov101_0229c868(p);
        func_ov002_0220a05c(p->unk_229C, res1, res2, 3, 1);
        p->unk_B6 = p->unk_8D;
        func_ov002_02208098(p, 10);
    }
}
