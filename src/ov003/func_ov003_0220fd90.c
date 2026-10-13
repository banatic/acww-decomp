/* func_ov003_0220fd90 @ 0x0220fd90, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220fd90(short *param1, short param2, int *param3);

void func_ov003_0220fd90(short *param1, short param2, int *param3)
{
    *param1 = param2;
    *(int *) (param1 + 2) = param3[0];
    *(int *) (param1 + 4) = param3[1];
    *(int *) (param1 + 6) = param3[2];
}
