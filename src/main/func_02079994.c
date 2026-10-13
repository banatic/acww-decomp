/* func_02079994 @ 0x02079994, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_02003704(int);
extern int func_02079b3c(int, int, int);
extern int func_02079b08(int, int, int);
extern int func_02079a88(int, int, int);
extern int func_02079a5c(int, int, int);
extern int func_02079a24(int, int, int);

int func_02079994(int r7, int r5, int r6)
{
    int r4 = 0;
    if (r5 == 0) {
        goto end;
    }
    if (func_02003704(func_0208150c(r5)) == 0) {
        goto end;
    }
    if (r6 == 0) {
        goto end;
    }
    if (func_02003704(func_0208150c(r6)) == 0) {
        goto end;
    }
    r4 = func_02079b3c(r7, func_0208150c(r5), func_0208150c(r6));
    r4 += func_02079b08(r7, r5, r6);
    r4 += func_02079a88(r7, r5, r6);
    r4 += func_02079a5c(r7, r5, r6);
    if (r4 >= 200) {
        goto end;
    }
    r4 -= func_02079a24(r7, r5, r6);
    if (r4 < 0) {
        r4 = -r4;
    }
end:
    return r4;
}
