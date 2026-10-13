/* func_ov003_02219a40 @ 0x02219a40, 0x22 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_ov003_02218388(int, int, int);

int func_ov003_02219a40(void)
{
    int ret;
    ret = func_02096718(4);
    if (ret) {
        return func_ov003_02218388(ret, 6, -1);
    }
    return 0;
}
