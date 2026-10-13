/* func_0206a694 @ 0x0206a694, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206a8f4(void *arg);
extern int func_0206837c(int value);
extern int func_020ab4a8(int value);

typedef struct {
    char pad_00[0x24];
    int unk_24;
} FuncArg;

int func_0206a694(FuncArg *arg)
{
    func_0206a8f4(arg);
    return func_020ab4a8(func_0206837c(arg->unk_24));
}
