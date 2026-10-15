/* func_0207ea10 @ 0x0207ea10, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996f8(int);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);

int func_0207ea10(int argument0)
{
    unsigned short val;
    unsigned short *p = func_020996f8((int) argument0);
    if (func_0204bcdc(p)) {
        val = 0x13bc;
        if (func_0204bc64(p) == func_0204bc64(&val)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*p == 0x13bc) {
            return 1;
        } else {
            return 0;
        }
    }
}
