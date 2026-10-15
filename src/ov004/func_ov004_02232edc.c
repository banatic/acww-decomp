/* func_ov004_02232edc @ 0x02232edc, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034240(void *, int, int, int, int);
extern int func_020341c8(void *, int);
extern void func_0203423c(void *);

void func_ov004_02232edc(char *self)
{
    char buf[0x44];
    int n = 0;
    int i;
    int f = 0;
    for (i = 0; i < 0x10; i++) {
        func_02034240(buf, i, 0xa, 0, 0);
        if (func_020341c8(buf, f) == 0) {
            n++;
        }
        func_0203423c(buf);
    }
    self[0x3522] = n;
}
