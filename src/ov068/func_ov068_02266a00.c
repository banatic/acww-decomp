/* func_ov068_02266a00 @ 0x02266a00, 0x22 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02227638(int arg);

int func_ov068_02266a00(int unused, int key, int value)
{
    int result = func_ov003_02227638(key);
    if (result != -1 && value == result) {
        return 1;
    }
    return 0;
}
