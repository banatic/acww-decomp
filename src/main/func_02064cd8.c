/* func_02064cd8 @ 0x02064cd8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064cf8(void);
extern void func_02001964(void *dst, int src);
extern char data_020de6a4[];

void func_02064cd8(int unused, int arg)
{
    if (func_02064cf8() == 0) {
        func_02001964(data_020de6a4, arg);
    }
}
