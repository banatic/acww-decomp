/* func_020095b0 @ 0x020095b0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    int data[4];
} UnkStruct_020095b0;

extern void func_0200e92c(UnkStruct_020095b0 *lp);
extern void func_0200e90c(UnkStruct_020095b0 *lp, int a, int b, int c);
extern void func_020095f0(int *data, int p2);
extern int func_0200e894(int p1, UnkStruct_020095b0 *lp);
extern void func_0200e91c(UnkStruct_020095b0 *lp);

int func_020095b0(int p1, int p2, int p3, int p4)
{
    UnkStruct_020095b0 local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x70, p3, p4);
    func_020095f0(local.data, p2);
    result = func_0200e894(p1, &local);
    func_0200e91c(&local);
    return result;
}
