/* func_0202fd78 @ 0x0202fd78, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202fb28(int *, int *);
extern int func_0202f904(int *, int *, int *, int *);
extern void func_01ffd070(int *, int *, int *);
extern int FX_MulFunc(int, int);

int func_0202fd78(int *arg0, int *arg1, int unused, int arg3)
{
    int flag = 0;
    int local4[3];
    int local16[3];
    int r7;

    r7 = func_0202fb28(arg0, arg1);
    if (r7 < 0) {
        goto end;
    }
    if (r7 > arg3 + 0x200) {
        goto end;
    }
    if (r7 >= arg3) {
        goto flag1;
    }

    func_01ffd070(local4, arg1, arg0 + 10);
    if (func_0202f904(arg0, local16, arg1, local4) == 0) {
        goto end;
    }
    if (r7 >= arg3) {
        goto flag2;
    }
    {
        int delta = arg3 - r7;
        arg1[0] += FX_MulFunc(delta, arg0[10]);
        arg1[1] += FX_MulFunc(delta, arg0[11]);
        arg1[2] += FX_MulFunc(delta, arg0[12]);
    }
flag2:
    flag = 1;
    goto end;
flag1:
    flag = 1;
end:
    return flag;
}
