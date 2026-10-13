/* func_0204edf8 @ 0x0204edf8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
} UnkStruct_0204edf8;

extern void func_02030e4c(int);
extern int func_02031b14(int, int);

int func_0204edf8(UnkStruct_0204edf8 *a, int b, int c)
{
    int result;
    func_02030e4c(a->unk_1C);
    result = func_02031b14(b, c);
    func_02030e4c(0);
    return result;
}
