/* func_ov004_0222b3e8 @ 0x0222b3e8, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    int data[4];
} UnkStruct_0222b3e8;

extern void func_0200e92c(UnkStruct_0222b3e8 *lp);
extern void func_0200e90c(UnkStruct_0222b3e8 *lp, int a, int b, int c);
extern void func_ov004_0222b428(int *data, int p2);
extern int func_0200e894(int p1, UnkStruct_0222b3e8 *lp);
extern void func_0200e91c(UnkStruct_0222b3e8 *lp);

int func_ov004_0222b3e8(int p1, int p2, int p3, int p4)
{
    UnkStruct_0222b3e8 local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0xd, p3, p4);
    func_ov004_0222b428(local.data, p2);
    result = func_0200e894(p1, &local);
    func_0200e91c(&local);
    return result;
}
