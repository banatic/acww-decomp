/* func_ov146_02299dec @ 0x02299dec, 0x3a bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200284c(int, int, int);
extern void func_ov146_02299d84(int);
extern void func_ov146_02299660(int, int);

void func_ov146_02299dec(int *param1, int param2)
{
    int *p;
    int temp;

    p = (int *) ((char *) param1 + 0xa4);
    *p = param2;
    func_0200284c(4, 0, *p - 0x38);
    temp = param2 >> 4;
    *(short *) ((char *) param1 + 0xae) = (short) temp;
    func_ov146_02299d84((int) param1);
    func_ov146_02299660((int) param1, 4);
}
