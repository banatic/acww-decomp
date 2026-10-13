/* func_ov004_02244f20 @ 0x02244f20, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a : 12;
    unsigned int b : 16;
    unsigned int c : 4;
} BF;
extern void func_020550e4(char *p, int a);
void func_ov004_02244f20(char *self)
{
    char *p = self + 0xb0;
    if (((BF *) (p + 0xa4))->b == 1) {
        func_020550e4(p, 2);
    } else {
        func_020550e4(p, 1);
    }
}
