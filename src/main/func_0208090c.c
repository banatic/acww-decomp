/* func_0208090c @ 0x0208090c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080a2c(unsigned int object);
extern int func_02082264(int);

int func_0208090c(unsigned int object)
{
    int r0;
    int r1;

    r0 = func_02080a2c(object);
    r1 = 0xc;
    if (r0 != 0) {
        r1 = func_02082264(r0);
    }
    return r1;
}
