/* func_020bb18c @ 0x020bb18c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not actually used
// placeholder, not actually used

void func_020bb18c(unsigned char *param0, int param1, unsigned short param2, unsigned int param3)
{
    unsigned char *ptr;
    unsigned int *ptr2;
    int offset;

    offset = param1 * 2;
    ptr = param0 + offset;
    *(unsigned short *) (ptr + 0x304) = param2;

    offset = param1 * 4;
    ptr2 = (unsigned int *) (param0 + offset);
    *(unsigned int *) ((unsigned char *) ptr2 + 0x308) = param3;
}
