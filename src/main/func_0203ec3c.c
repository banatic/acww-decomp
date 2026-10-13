/* func_0203ec3c @ 0x0203ec3c, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070094(void);
extern int func_02095e08(void);
extern int func_02095ce0(void);
extern int func_0207004c(int);

int func_0203ec3c(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    if (func_02070094() == 0) {
        return 0;
    }
    if (func_02095e08() == 0) {
        return 0;
    }
    if (func_02095ce0() == 0) {
        return 0;
    }
    func_0207004c(*(unsigned char *) (r4 + 0x16));
    return 1;
}
