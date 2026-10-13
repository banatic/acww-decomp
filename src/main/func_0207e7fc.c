/* func_0207e7fc @ 0x0207e7fc, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020996f8(void);
extern int func_0204bcdc(int);
extern int func_0204bc64(int);

int func_0207e7fc(void)
{
    int a = func_020996f8();
    if (func_0204bcdc(a)) {
        unsigned short local = 0x1406;
        if (func_0204bc64(a) == func_0204bc64((int) &local)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) a == 0x1406) {
            return 1;
        } else {
            return 0;
        }
    }
}
