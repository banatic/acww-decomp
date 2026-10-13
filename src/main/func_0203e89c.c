/* func_0203e89c @ 0x0203e89c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095bdc(void);
extern void func_0203ea80(int, int);
extern void func_0203f364(void);

int func_0203e89c(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    if (func_02095bdc() != 0) {
        func_0203ea80(r4, 8);
        func_0203f364();
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
