/* func_ov003_02215240 @ 0x02215240, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *s);
extern void func_0200e90c(void *s, int size, int c, int d);
extern int func_0200e894(void *a, void *s);
extern int func_0200e91c(void *s);

struct UnkStruct_02215240 {
    char data[0xc];
    char flag;
    char pad_0D[0x1c - 0xd];
};

int func_ov003_02215240(void *a, char b, int c, int d)
{
    struct UnkStruct_02215240 local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x54, c, d);
    local.flag = b;
    result = func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}
