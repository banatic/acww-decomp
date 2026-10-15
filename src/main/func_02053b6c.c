/* func_02053b6c @ 0x02053b6c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern int func_02053b8c(int);

int func_02053b6c(int param)
{
    if (func_0204bcdc(param) != 0) {
        return func_02053b8c((int) func_0204bc64(param));
    }
    return 0;
}
