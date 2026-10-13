/* func_02080c84 @ 0x02080c84, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int x);
extern int func_02003704(int x);
extern int func_02003648(int x);
extern unsigned short *func_02082500(int x);

void func_02080c84(unsigned short *out, int param1)
{
    unsigned short *result;
    unsigned int r1;
    unsigned short outval;

    *out = 0x11a8;
    if (func_02003704(func_0208150c(param1))) {
        result = func_02082500(func_02003648(func_0208150c(param1)));
        if (result != 0) {
            r1 = result[0x16];
            if (r1 < 0x100) {
                outval = (r1 + 0x11a8) & 0xffff;
            } else {
                outval = 0x11a8;
            }
            *out = outval;
        }
    }
}
