/* func_ov046_02260664 @ 0x02260664, 0x28 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

void func_ov046_02260664(void *arg0, int arg1)
{
    if (arg1 == 0) {
        *(int *) ((char *) arg0 + 0xdc) = 0x30;
    } else if (arg1 == 1) {
        *(unsigned char *) ((char *) arg0 + 0xc6) = 1;
        *(int *) ((char *) arg0 + 0xdc) = 0x15;
    } else {
        *(int *) ((char *) arg0 + 0xdc) = 0x16;
    }
}
