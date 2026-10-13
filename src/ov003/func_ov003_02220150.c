/* func_ov003_02220150 @ 0x02220150, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cef0[];

int func_ov003_02220150(int x)
{
    unsigned int i;
    for (i = 0; i < 32; i++) {
        if (data_ov003_0223cef0[i] == x) {
            return (int) i;
        }
    }
    return -1;
}
