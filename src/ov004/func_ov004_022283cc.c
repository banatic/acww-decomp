/* func_ov004_022283cc @ 0x022283cc, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    int data[4];
} UnkStruct_022283cc;

extern void func_0200e92c(UnkStruct_022283cc *lp);
extern void func_0200e90c(UnkStruct_022283cc *lp, int a, int b, int c);
extern void func_ov004_0222840c(int *data, int p2);
extern int func_0200e894(int p1, UnkStruct_022283cc *lp);
extern void func_0200e91c(UnkStruct_022283cc *lp);

int func_ov004_022283cc(int p1, int p2, int p3, int p4)
{
    UnkStruct_022283cc local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x2e, p3, p4);
    func_ov004_0222840c(local.data, p2);
    result = func_0200e894(p1, &local);
    func_0200e91c(&local);
    return result;
}
