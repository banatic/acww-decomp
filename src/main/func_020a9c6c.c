/* func_020a9c6c @ 0x020a9c6c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9c4c(void *);
extern int func_020edf70(int);

void func_020a9c6c(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result != 0) {
        func_020a9c4c((void *) result);
    }
}
