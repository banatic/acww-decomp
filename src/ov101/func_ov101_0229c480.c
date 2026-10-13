/* func_ov101_0229c480 @ 0x0229c480, 0x2c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f9c0(void *);
extern void func_ov002_02208d4c(void *, int, int);

typedef struct {
    char pad_00[0x26e8];
    int value;
} UnkStruct_0229c480;

void func_ov101_0229c480(UnkStruct_0229c480 *arg)
{
    int result = func_0206f9c0(arg);
    func_ov002_02208d4c(&arg->value, result, 0);
    func_ov002_02208d4c(&arg->value, 2, 1);
}
