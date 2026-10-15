/* func_02051b9c @ 0x02051b9c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02051b7c(void *);
extern int func_020edf70(int);

void func_02051b9c(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_02051b7c((void *) result);
}
