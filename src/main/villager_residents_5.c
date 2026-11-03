/* villager_residents_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207c048 @ 0x0207c048, 0x78 bytes, Thumb
 * func_0207bfdc @ 0x0207bfdc, 0x6c bytes, Thumb
 */

extern int func_0207cad4(void *);
extern int func_0207c160(char *);
extern int func_0207c0c0(char *);
extern int func_0209e3ac(int, char *, int);
extern int func_0209e380(char *, int);
extern int func_020644cc(int);
extern int func_0207b3dc(char *);
extern unsigned int func_0208150c(char *);
extern int func_02003704(void *);
extern int func_0207dca8(char *);
extern int func_0207cc54(unsigned char, int, int);

int func_0207c048(char *arg0, int arg1)
{
    int v6, v0, result, ret;

    if (func_0207cad4(arg0) != 8) {
        goto fail;
    }
    v6 = func_0207c160(arg0);
    v0 = func_0207c0c0(arg0);
    if (v6 != -1) {
        goto fail;
    }
    if (v0 != -1) {
        goto fail;
    }
    if (func_0209e3ac(arg1, arg0 + 0x4050, 0x3f) != 1) {
        goto fail;
    }
    result = func_0209e380(arg0 + 0x4050, arg1);
    if (result <= 0) {
        goto fail;
    }
    if (result >= 4) {
        ret = 1;
    } else {
        ret = (func_020644cc(4 - result) == 0);
    }
    if (ret) {
        return 1;
    } else {
        return 0;
    }
fail:
    return 0;
}

int func_0207bfdc(char *param)
{
    char *ptr = param;
    int result = func_0207b3dc(param);
    unsigned char flags = 0;
    int count = 0;
    int i;
    for (i = 0; i < 8; ptr += 0x7ec, i++) {
        if ((i == ((signed char *) param)[0x4075]) || (i == result)) {
            continue;
        }
        if (func_02003704((void *) func_0208150c(ptr)) == 0) {
            continue;
        }
        if (func_0207dca8(ptr) == 0) {
            continue;
        }
        flags |= 1 << i;
        count++;
    }

    return func_0207cc54(flags, count, 8);
}
