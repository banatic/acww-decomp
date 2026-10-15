/* func_0209446c @ 0x0209446c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *s, int b, int c, int d);
extern void func_0203423c(void *s);
extern int func_02094cf8(int sign, int a, int b, int c, int d, int zero);

typedef struct {
    char pad_00[52];
    int unk_34;
    char pad_38[12];
} UnkStruct_0209446c;

int func_0209446c(int a, int b, int c, int d)
{
    UnkStruct_0209446c s;
    int sign;
    int result;

    func_02034270(&s, b, 0, 0);
    if (s.unk_34 == 19) {
        sign = 45;
    } else {
        sign = 43;
    }
    result = func_02094cf8(sign, a, b, c, d, 0);
    func_0203423c(&s);
    return result;
}
