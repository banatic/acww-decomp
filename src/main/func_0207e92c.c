/* func_0207e92c @ 0x0207e92c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996f8(void);
extern int func_0204bcdc(void);
extern int func_0204bc64(unsigned short *ptr);

int func_0207e92c(void)
{
    unsigned short *p = func_020996f8();
    if (func_0204bcdc()) {
        unsigned short temp = 0x13ea;
        int a = func_0204bc64(p);
        int b = func_0204bc64(&temp);
        if (a == b) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13ea) {
            return 1;
        } else {
            return 0;
        }
    }
}
