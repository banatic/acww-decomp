/* func_ov068_02273088 @ 0x02273088, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02273230(void *, int);
extern void *data_ov068_022787fc;

int func_ov068_02273088(void)
{
    void *ptr = data_ov068_022787fc;
    if (ptr != 0) {
        return func_ov068_02273230(ptr, 1);
    }
    return 1;
}
