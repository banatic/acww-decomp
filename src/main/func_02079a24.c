/* func_02079a24 @ 0x02079a24, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02080890(void *);

int func_02079a24(int unused, void *arg1, void *arg2)
{
    void *f1 = func_02080890(arg1);
    void *f2 = func_02080890(arg2);
    int result = 0;
    if (f1 && f2) {
        unsigned char b = ((unsigned char *) f2)[4];
        unsigned char a = ((unsigned char *) f1)[4];
        if (a > b) {
            result = a - b;
        } else {
            result = b - a;
        }
    }
    return result;
}
