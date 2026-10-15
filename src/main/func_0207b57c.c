/* func_0207b57c @ 0x0207b57c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207b78c(void *);
extern void func_0207b594(int);

void func_0207b57c(int r0)
{
    int r4;
    int result;

    r4 = r0;
    result = func_0207b78c((void *) r0);
    if (result != 0) {
        func_0207b594(r4);
    }
}
