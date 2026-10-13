/* func_020938a8 @ 0x020938a8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[12];
    int *ptr;
} ArgType;

extern void func_02094c38(void *ptr, int a, int b);

void func_020938a8(ArgType *arg)
{
    int zero = 0;
    func_02094c38(arg, zero, zero);
    arg->ptr[21] = 0x99a;
}
