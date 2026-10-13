/* func_020803e0 @ 0x020803e0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081edc(void *);

int func_020803e0(void *ptr)
{
    int count = 0;
    int i;
    for (i = count; i < 8; i++) {
        if (func_02081edc(ptr) != 0) {
            count++;
        }
        ptr = (char *) ptr + 0x80;
    }
    return count;
}
