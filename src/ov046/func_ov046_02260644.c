/* func_ov046_02260644 @ 0x02260644, 0x1e bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov046_022610fc(unsigned char *arg0);

void func_ov046_02260644(int *param0, int param1)
{
    if (param1 == 0) {
        param0[55] = 0x3b;
    } else {
        param0[55] = func_ov046_022610fc((unsigned char *) param0);
    }
}
