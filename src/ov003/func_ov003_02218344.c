/* func_ov003_02218344 @ 0x02218344, 0x42 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern void func_0200e91c(void *);

struct UnkStruct_02218344 {
    char data[0x1c];
};

int func_ov003_02218344(int a, int b, int c, int d, short e)
{
    struct UnkStruct_02218344 local;
    char *p;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x3b, d, e);
    p = &local.data[0xc];
    p[0] = (char) b;
    p[1] = (char) c;
    result = func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}
