/* func_020bb7e0 @ 0x020bb7e0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020bb830(void *, int);

void func_020bb7e0(char *out, int a, int b)
{
    void *x;
    void *y;

    x = func_020bb830(out, a);
    y = func_020bb830(out, b);
    if (x) {
        *(void **) (out + 0x1534) = x;
    } else if (y) {
        *(void **) (out + 0x1534) = y;
    } else {
        *(void **) (out + 0x1534) = 0;
    }
    *(int *) (out + 0x1524) = a;
    *(int *) (out + 0x1528) = b;
}
