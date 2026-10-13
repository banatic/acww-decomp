/* func_020c2300 @ 0x020c2300, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8840(void *ptr);
extern void func_020c26b4(void *ptr, int value);

int func_020c2300(void *ptr)
{
    if (func_020e8840((char *) ptr + 0x714) == 0) {
        func_020c26b4(ptr, 5);
    }
    return 1;
}
