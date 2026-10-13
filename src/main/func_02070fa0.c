/* func_02070fa0 @ 0x02070fa0, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02070fa0(int arg0);

extern int func_02070edc(int arg0);
extern int func_02070e98(int arg0);
extern int func_02070f5c(int arg0);
extern int func_02070f1c(int arg0);

int func_02070fa0(int arg0)
{
    int result;
    if (func_02070edc(arg0) == 0) {
        result = 0;
    } else if (func_02070e98(arg0) == 0) {
        result = 0;
    } else if (func_02070f5c(arg0) == 0) {
        result = 0;
    } else if (func_02070f1c(arg0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
