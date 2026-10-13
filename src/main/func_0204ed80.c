/* func_0204ed80 @ 0x0204ed80, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
} UnkStruct_0204ed80;

extern void func_02030e4c(int arg);
extern int func_02031aa0(int a, int b);

int func_0204ed80(UnkStruct_0204ed80 *a, int b, int c)
{
    int ret;
    func_02030e4c(a->unk_1C);
    ret = func_02031aa0(b, c);
    func_02030e4c(0);
    return ret;
}
