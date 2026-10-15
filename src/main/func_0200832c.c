/* func_0200832c @ 0x0200832c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbc0(void);
extern int func_0203e19c(void);
extern int func_0200d4e8(int, int, int, int);

void func_0200832c(int arg0)
{
    int r4;
    int r0;

    r4 = arg0;
    r0 = func_0206fbc0();
    if (r0 != 0) {
        func_0203e19c();
        func_0200d4e8(r4, 3, 1, -1);
    }
}
