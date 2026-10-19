/* func_020f4eec @ 0x020f4eec, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned long func_020efc18(const unsigned long *stream);
extern int func_020efc2c(int a, int b);
extern void func_020efc44(int a, int b);

void func_020f4eec(int a, int b)
{
    int found = 1;
    int v;
    v = func_020efc18((const unsigned long *) a);
    while (v != 0) {
        if (v == b) {
            found = 0;
            break;
        }
        v = func_020efc2c(a, v);
    }
    if (found == 0) {
        return;
    }
    func_020efc44(a, b);
}
