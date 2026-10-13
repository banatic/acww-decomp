/* func_0204b710 @ 0x0204b710, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b790(void);
extern int func_0204b784(int);
extern int func_0204b778(int);
extern int func_0204b76c(int);
extern int func_0204b760(int);

int func_0204b710(int p)
{
    int result = 0;
    if (func_0204b790() == 0) {
        if (func_0204b784(p) != 0) {
            result = 1;
        } else if (func_0204b778(p) != 0) {
            result = 2;
        } else if (func_0204b76c(p) != 0) {
            result = 3;
        } else if (func_0204b760(p) != 0) {
            result = 4;
        }
    }
    return result;
}
