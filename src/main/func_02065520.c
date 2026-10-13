/* func_02065520 @ 0x02065520, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065564(void *);

void func_02065520(void *arg0)
{
    int i;
    void *ptr;

    ptr = arg0;
    for (i = 0; i < 4; i++) {
        func_02065564(ptr);
    }
}
