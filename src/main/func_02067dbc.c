/* func_02067dbc @ 0x02067dbc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02067e04(unsigned char *param);
extern int func_020a80c4(int a, int b, int c, int d);
extern int func_020a7fd4(void);
extern int func_020a7fac(void);

int func_02067dbc(unsigned char *param)
{
    int r4 = 0;
    if (param[0x1e98] != 0) {
        goto end;
    }
    if (func_02067e04(param) != 0) {
        goto end;
    }
    if (func_020a80c4(8, 0xf8, 0x70, 0xc0) == 0) {
        goto next;
    }
    r4 = 1;
    goto end;
next:
    if (func_020a7fd4() != 0) {
        goto set_r4;
    }
    if (func_020a7fac() == 0) {
        goto end;
    }
set_r4:
    r4 = 1;
end:
    return r4;
}
