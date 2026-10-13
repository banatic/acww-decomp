/* func_0207ea5c @ 0x0207ea5c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020996f8(void);
extern int func_0204bcdc(void);
extern int func_0204bc64(int);

int func_0207ea5c(void)
{
    int r4;
    int r0;
    unsigned short local;

    r4 = func_020996f8();
    if (func_0204bcdc() != 0) {
        local = 0x13a8;
        r4 = func_0204bc64(r4);
        r0 = func_0204bc64((int) &local);
        if (r4 == r0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) r4 == 0x13a8) {
            return 1;
        } else {
            return 0;
        }
    }
}
