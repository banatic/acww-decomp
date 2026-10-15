/* func_ov003_0220e548 @ 0x0220e548, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(void *p1, int a, int b, int c);
extern int func_0200dc8c(void *p1);
extern int func_0200dc80(void *p1);
extern void func_0200f268(void *p1, int a);
extern int func_0200fbe0(void *p1);
extern void func_0205eae0(void *p1, int a, int b, int c);
extern void func_0205eac4(void *p1, int a);

typedef struct UnkStruct_0220e548 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
    int unk_18;
} UnkStruct_0220e548;

void func_ov003_0220e548(void *p1, void *p2, int previous)
{
    int x;
    UnkStruct_0220e548 *sub;

    func_020109fc(p1, 0x92, 3, 0);
    *(int *) ((char *) p1 + 0x2e0) = 0x800;
    x = *(int *) ((char *) p2 + 0xc);
    sub = (UnkStruct_0220e548 *) ((char *) p1 + 0x7d4);
    sub->unk_04 = 0x800;
    sub->unk_08 = 0x800;
    sub->unk_0C = 0;
    sub->unk_10 = 0;
    *(int *) ((char *) p1 + 0x7d4) = func_0200dc8c(p1);
    sub->unk_14 = (short) func_0200dc80(p1);
    sub->unk_18 = x;
    func_0200f268(p1, 9);
    if (func_0200fbe0(p1) == 4) {
        func_0205eae0((char *) p1 + 0x5a0, 0x11, 3, 0);
        func_0205eac4((char *) p1 + 0x5a0, 0x800);
    }
}
