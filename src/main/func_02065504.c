/* func_02065504 @ 0x02065504, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065560(void *);

void func_02065504(void *arg)
{
    int i;
    void *ptr = arg;

    for (i = 0; i < 4; i++) {
        func_02065560(ptr);
    }
}
