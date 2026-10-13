/* func_020936bc @ 0x020936bc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *p, int a, int b, int c);
extern void func_0203423c(void *p);
extern int func_02094cf8(int a, int b, int c, int d, int e, void *f);
extern unsigned char data_020e27cc[];

int func_020936bc(int a, int b, int c, int d)
{
    struct {
        unsigned char pad[52];
        unsigned int field;
        unsigned char pad2[12];
    } local;
    int code;
    int result;

    func_02034270(&local, b, 0, 0);
    if (local.field == 0x13) {
        code = 0x6f;
    } else {
        code = 0x6e;
    }
    result = func_02094cf8(code, a, b, c, d, data_020e27cc);
    func_0203423c(&local);
    return result;
}
