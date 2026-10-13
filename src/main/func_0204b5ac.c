/* func_0204b5ac @ 0x0204b5ac, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b5f4(int);
extern int func_0204b6e0(int);
extern int func_0204b6ac(int);
extern int func_0204b678(int);

int func_0204b5ac(int p)
{
    int res = -1;
    if (func_0204b5f4(p) != 0) {
        if (func_0204b6e0(p) != 0) {
            res = 1;
        } else if (func_0204b6ac(p) != 0) {
            res = 2;
        } else if (func_0204b678(p) != 0) {
            res = 3;
        } else {
            res = 4;
        }
    }
    return res;
}
