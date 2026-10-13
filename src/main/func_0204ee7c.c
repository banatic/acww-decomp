/* func_0204ee7c @ 0x0204ee7c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030e4c(int arg);
extern int func_02031b38(int a, int b);

typedef struct {
    unsigned char pad_00[0x1c];
    int unk_1C;
} Func0204ee7c_Struct;

int func_0204ee7c(Func0204ee7c_Struct *obj, int a, int b)
{
    int result;
    func_02030e4c(obj->unk_1C);
    result = func_02031b38(a, b);
    func_02030e4c(0);
    return result;
}
