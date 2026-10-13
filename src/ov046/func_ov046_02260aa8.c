/* func_ov046_02260aa8 @ 0x02260aa8, 0x14 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

void func_ov046_02260aa8(int param1, int param2)
{
    if (param2 == 0) {
        *(int *) ((char *) param1 + 0xdc) = 9;
    } else {
        *(int *) ((char *) param1 + 0xdc) = 0x23;
    }
}
