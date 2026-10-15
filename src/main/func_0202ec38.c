/* func_0202ec38 @ 0x0202ec38, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203efdc(char *);
extern void func_02082544(void *);

int func_0202ec38(void *arg0)
{
    int r4;
    int result;

    r4 = (int) arg0;
    if (func_0203efdc(arg0) == 0) {
        return 0;
    }
    func_02082544((void *) (r4 + 0xea));
    return 1;
}
