/* func_0203adb0 @ 0x0203adb0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *data_021c67a4;

unsigned int func_0203adb0(void)
{
    unsigned int *ptr;
    unsigned int offset;
    unsigned int result;

    ptr = data_021c67a4;
    offset = 0x1e8;
    result = *(unsigned int *) ((unsigned char *) ptr + offset);
    return result;
}
