/* func_020604e8 @ 0x020604e8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020604e8(void *ptr);

int func_020604e8(void *ptr)
{
    int value;
    value = *(int *) ((char *) ptr + 4);
    value -= 4;
    if ((unsigned int) value > 1) {
        return 0;
    }
    return 1;
}
