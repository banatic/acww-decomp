/* func_02073ca8 @ 0x02073ca8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02073ca8(int *ptr)
{
    int *p = ptr + 3;
    int i;
    for (i = 2; i >= 0; i--) {
        *p++ = 3;
    }
}
