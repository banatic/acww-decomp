/* func_0207e9c4 @ 0x0207e9c4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996f8(void);
extern int func_0204bcdc(void);
extern int func_0204bc64(const unsigned short *);

int func_0207e9c4(void)
{
    unsigned short local;
    unsigned short *p = func_020996f8();

    if (func_0204bcdc() != 0) {
        local = 0x1405;
        if (func_0204bc64(p) == func_0204bc64(&local)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (p[0] == 0x1405) {
            return 1;
        } else {
            return 0;
        }
    }
}
