/* func_020989e0 @ 0x020989e0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209985c(int);
extern int func_020a1368(void);

int func_020989e0(int object)
{
    int n;
    int x;
    n = func_0209985c(object);
    if (n >= 0 && n < 4 && (x = func_020a1368()) != 0) {
        return x + 0x3200 * n;
    }
    return 0;
}
