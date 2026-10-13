/* func_ov136_0229ca28 @ 0x0229ca28, 0x62 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ca28 UnkStruct_0229ca28;
struct UnkStruct_0229ca28 {
    char pad_00[0x94];
    char unk_94;
    char pad_95[0xf8 - 0x94 - 1];
    char unk_F8;
};

extern int func_ov002_0220a700(void *s);
extern int func_0208e4bc(void *s);
extern int func_ov002_0220a6e0(void *s);
extern int func_ov002_0220a768(void *s, int arg);
extern int func_ov002_0220a72c(void *s, int arg);
extern void func_ov002_0220a0b4(void *s, int a, int b);
extern void func_ov136_0229c734(UnkStruct_0229ca28 *p);
extern void func_ov002_022080a0(UnkStruct_0229ca28 *p, int a);

void func_ov136_0229ca28(UnkStruct_0229ca28 *p)
{
    if (func_ov002_0220a700(&p->unk_F8) != 0) {
        if (func_0208e4bc(&p->unk_94) != 0) {
            int t1 = func_ov002_0220a6e0(&p->unk_F8);
            int t2 = func_ov002_0220a768(&p->unk_F8, -1);
            int t3 = func_ov002_0220a72c(&p->unk_F8, -1);
            func_ov002_0220a0b4(&p->unk_94, t1 + t2, t1 + t3);
        }
    } else {
        func_ov136_0229c734(p);
        func_ov002_022080a0(p, 1);
    }
}
