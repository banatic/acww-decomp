/* func_020abb2c @ 0x020abb2c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aca54(void *ptr);
extern void func_020abb08(void *ptr);

void func_020abb2c(void *ptr)
{
    if (func_020aca54((char *) ptr + 0xe4)) {
        func_020abb08(ptr);
    }
}
