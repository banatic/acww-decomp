/* func_020a7bd0 @ 0x020a7bd0, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not actually used

void func_020a7bd0(unsigned char *param0)
{
    unsigned char *ptr;
    unsigned char value;

    if (*(unsigned int *) (param0 + 0x24) == 3) {
        ptr = param0 + 0x58;
        value = 1;
        *ptr = value;
    }
}
