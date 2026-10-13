/* func_0204678c @ 0x0204678c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_0204a3cc(int *ptr, int val);
extern int data_021c79c4;

int func_0204678c(void)
{
    int r = func_0204e414();
    int ret = 5;
    if (r != 0) {
        ret = func_0204a3cc(&data_021c79c4, r);
    }
    return ret;
}
