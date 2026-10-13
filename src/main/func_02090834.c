/* func_02090834 @ 0x02090834, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090764(void *);

void func_02090834(void *param)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_02090764((char *) param + i * 0x530);
    }
}
