/* func_ov101_0229cff0 @ 0x0229cff0, 0x64 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x229c];
    char unk_229C;
    char pad_229D[0x573];
    char unk_2810;
} UnkStruct_0229cff0;

extern int func_ov002_0220a700(void *p);
extern int func_0208e4bc(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int a);
extern int func_ov002_0220a72c(void *p, int a);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov101_0229c4ac(void *p);

void func_ov101_0229cff0(UnkStruct_0229cff0 *p)
{
    if (func_ov002_0220a700(&p->unk_2810) != 0) {
        if (func_0208e4bc(&p->unk_229C) != 0) {
            int r4, r6, r2;
            r4 = func_ov002_0220a6e0(&p->unk_2810);
            r6 = func_ov002_0220a768(&p->unk_2810, -1);
            r2 = func_ov002_0220a72c(&p->unk_2810, -1);
            func_ov002_0220a0b4(&p->unk_229C, r4 + r6, r4 + r2);
        }
    } else {
        func_ov101_0229c4ac(p);
    }
}
