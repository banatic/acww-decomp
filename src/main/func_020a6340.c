/* func_020a6340 @ 0x020a6340, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a6340(void *param);

void func_020a6340(void *param)
{
    unsigned char *ptr;
    int i;

    ptr = (unsigned char *) param + 0x68;
    for (i = 3; i >= 0; i--) {
        *ptr = 0;
        ptr++;
    }
}
