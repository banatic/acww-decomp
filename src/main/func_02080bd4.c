/* func_02080bd4 @ 0x02080bd4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_02003704(int);
extern int func_02003648(int);
extern int func_02082500(int);

void func_02080bd4(unsigned short *out, int arg1)
{
    int b;
    unsigned char v;
    unsigned short value;

    *out = 0x1380;
    if (func_02003704(func_0208150c(arg1)) != 0) {
        b = func_02082500(func_02003648(func_0208150c(arg1)));
        if (b != 0) {
            v = *(unsigned char *) (b + 0x2e);
            if (v < 0x20) {
                value = 0x1380 + v;
            } else {
                value = 0x1380;
            }
            *out = value;
        }
    }
}
