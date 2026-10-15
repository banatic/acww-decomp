/* func_0207e8e0 @ 0x0207e8e0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996f8(int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(unsigned short *p);

int func_0207e8e0(int argument0)
{
    unsigned short *p;
    unsigned short local;

    p = func_020996f8((int) argument0);
    if (func_0204bcdc(p) != 0) {
        local = 0x13f5;
        if (func_0204bc64(p) == func_0204bc64(&local)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13f5) {
            return 1;
        } else {
            return 0;
        }
    }
}
