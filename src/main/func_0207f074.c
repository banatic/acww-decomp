/* func_0207f074 @ 0x0207f074, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int);
extern int func_02099640(int);
extern int func_0208150c(int);
extern int func_02003704(int);
extern int func_0207f150(int);
extern int func_0207f1d8(int);
extern int func_0207ef54(int, int);

int func_0207f074(int x)
{
    int temp;
    temp = func_02099640(func_020984e8(x));
    if (func_02003704(func_0208150c(x)) == 0) {
        goto fail;
    }
    if (func_0207f150(x) != 3) {
        goto fail;
    }
    if (func_0207f1d8(x) == 2) {
        goto fail;
    }
    if (func_0207ef54(x, temp) != 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
