/* func_0200eebc @ 0x0200eebc, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fbe0(void *p);
extern void func_0205eae0(void *base, int a, int b, int c);

void func_0200eebc(void *p)
{
    int status;

    status = func_0200fbe0(p);
    if (status == 4) {
        func_0205eae0((char *) p + 0x5a0, 0, 9, 0);
    } else if (status == 3) {
        func_0205eae0((char *) p + 0x5a0, 0x13, 3, 0);
    } else if (status == 0xa) {
        func_0205eae0((char *) p + 0x5a0, 0x23, 3, 0);
    } else if (status == 6) {
        func_0205eae0((char *) p + 0x5a0, 0x21, 3, 0);
    }
}
