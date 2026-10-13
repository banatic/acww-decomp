/* func_0207ffdc @ 0x0207ffdc, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned char *);
extern int func_02003704(int);
extern int func_02003648(int);
extern int func_02082500(int);
extern int func_0207f1c8(unsigned char *);
extern int func_0209b5ec(int);
extern int func_0209c330(int);
extern int func_0209c2c0(int);

int func_0207ffdc(unsigned char *param0, int *param1, int *param2)
{
    int ret = 0;
    int x;

    if (func_02003704(func_0208150c(param0)) == 0) {
        goto exit;
    }
    if (func_02082500(func_02003648(func_0208150c(param0))) == 0) {
        goto exit;
    }

    x = func_0209b5ec(func_0207f1c8(param0));

    if (func_0209c330(x) == 2) {
        goto normal;
    }
    if (func_0209c330(x) == 8) {
        goto check2;
    }
    if (func_0209c330(x) == 9) {
        goto check2;
    }
    if (func_0209c330(x) == 10) {
        goto check2;
    }
    if (func_0209c330(x) != 11) {
        goto other;
    }

check2:
    if (func_0209c2c0(x) == 0) {
        goto other;
    }

normal:
    *param1 = 3;
    *param2 = param0[0x7d8] % 10;
    goto success;

other:
    *param1 = 2;
    *param2 = param0[0x7d8];

success:
    ret = 1;

exit:
    return ret;
}
