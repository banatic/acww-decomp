/* func_0207eaa8 @ 0x0207eaa8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned short *func_020996f8(const unsigned short *str);
extern int func_0204bcdc(void *);
extern int func_0204bc64(const unsigned short *str);

int func_0207eaa8(const unsigned short *str)
{
    const unsigned short *p = func_020996f8(str);
    if (func_0204bcdc((void *) p)) {
        unsigned short tmp[4];
        int a, b;
        tmp[0] = 0x13b2;
        a = func_0204bc64(p);
        b = func_0204bc64(tmp);
        if (a == b) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (p[0] == 0x13b2) {
            return 1;
        } else {
            return 0;
        }
    }
}
