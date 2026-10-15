/* func_ov068_0226aca8 @ 0x0226aca8, 0x9a bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_020951bc(void *argument0);
extern int func_020807a8(int, int);
extern int func_02081d20(int);
extern int func_020644cc(int);

int func_ov068_0226aca8(int unused, int *out1, int *out2, int val1, int val2)
{
    int sp0;
    int a;
    int b;
    int c;
    int d;

    if (func_020984e8()) {
        sp0 = func_02099870(func_020984e8());
    } else {
        sp0 = 0;
    }
    if (sp0 == 0 || func_020951bc((void *) sp0) == 0) {
        goto fail;
    }

    a = -128;
    b = -128;

    c = func_020807a8(val1, sp0);
    d = func_020807a8(val2, sp0);

    if (c) {
        a = func_02081d20(c);
    }
    if (d) {
        b = func_02081d20(d);
    }

    if (a > b) {
        goto success0;
    }
    if (a != b) {
        goto success1;
    }
    if (func_020644cc(2) != 0) {
        goto success1;
    }

success0:
    *out1 = val1;
    *out2 = val2;
    return 0;

success1:
    *out1 = val2;
    *out2 = val1;
    return 1;

fail:
    *out1 = val1;
    *out2 = val2;
    return 0;
}
