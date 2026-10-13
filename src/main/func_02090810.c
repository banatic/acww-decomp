/* func_02090810 @ 0x02090810, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090740(void *ptr);

void func_02090810(void *ptr)
{
    int i;
    void *base;

    base = ptr;
    for (i = 0; i < 4; i++) {
        func_02090740((char *) base + i * 0x530);
    }
}
