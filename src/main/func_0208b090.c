/* func_0208b090 @ 0x0208b090, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011ed4(void);
extern int func_02011f3c(void);
extern void func_0208b2b0(int);
extern void func_0208b344(int);
extern void func_0208b22c(int);
extern void func_0208b1d4(int);
extern void func_0208b374(int);

void func_0208b090(int param)
{
    int result;

    result = func_02011ed4();
    if (result == 1) {
        if (func_02011f3c() != 0) {
            func_0208b2b0(param);
        } else {
            func_0208b344(param);
        }
    } else if (result == 2) {
        func_0208b22c(param);
    } else if (result == 3) {
        func_0208b1d4(param);
    } else {
        func_0208b374(param);
    }
}
