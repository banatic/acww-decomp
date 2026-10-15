/* func_0204df08 @ 0x0204df08, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67e8(unsigned int);
extern int func_020b6818(int);
extern int func_0204df30(int);

int func_0204df08(int param)
{
    int result;
    int temp;

    result = 0;
    if (func_020b67e8(param) != 0) {
        temp = func_020b6818(param);
        result = func_0204df30(temp);
    }
    return result;
}
