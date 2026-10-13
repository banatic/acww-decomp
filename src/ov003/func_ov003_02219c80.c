/* func_ov003_02219c80 @ 0x02219c80, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);

int func_ov003_02219c80(void)
{
    int result;
    int *ptr;

    result = func_02096718(4);
    if (result != 0) {
        ptr = (int *) result;
        if (ptr[0x1fc] == 6) {
            if (((unsigned char *) ptr)[0x7e1] == 1) {
                return 1;
            }
        }
    }
    return 0;
}
