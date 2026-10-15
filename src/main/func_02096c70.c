/* func_02096c70 @ 0x02096c70, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096c50(void *);
extern void *func_020edf70(unsigned int);

void func_02096c70(void)
{
    void *ptr;

    ptr = func_020edf70(0x50);
    if (ptr != 0) {
        func_02096c50(ptr);
    }
}
