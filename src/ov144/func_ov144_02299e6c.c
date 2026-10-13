/* func_ov144_02299e6c @ 0x02299e6c, 0x3a bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200284c(int, int, int);
extern void func_ov144_02299df4(int);
extern void func_ov144_02299670(int, int);

void func_ov144_02299e6c(int *param0, int param1)
{
    int *p;
    int temp;

    p = (int *) ((char *) param0 + 0x9c);
    *p = param1;
    func_0200284c(4, 0, *p - 0x18);
    temp = param1 >> 4;
    *(short *) ((char *) param0 + 0xb6) = (short) temp;
    func_ov144_02299df4((int) param0);
    func_ov144_02299670((int) param0, 4);
}
