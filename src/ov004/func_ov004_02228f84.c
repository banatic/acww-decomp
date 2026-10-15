/* func_ov004_02228f84 @ 0x02228f84, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(void *parameter0, unsigned int *parameter1, int parameter2);
extern int func_020778f8(int);

void func_ov004_02228f84(int a1, int a2, int a3, short *a4)
{
    int r5 = a1;
    short *r4 = a4;
    func_02077978((void *) (a1), (unsigned int *) (a2), (int) (a3));
    *r4 = (short) func_020778f8(r5 + 5);
}
