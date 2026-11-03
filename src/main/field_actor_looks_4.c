/* field_actor_looks_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02011138 @ 0x02011138, 0x18 bytes, Thumb
 * func_0201111c @ 0x0201111c, 0x1a bytes, Thumb
 * func_020110e8 @ 0x020110e8, 0x32 bytes, Thumb
 * func_020110c4 @ 0x020110c4, 0x24 bytes, Thumb
 */

extern unsigned short *func_020996e0(void *arg);
extern int func_02011368(void *);
extern int func_0209975c(int);
extern int func_0209984c(void *);
extern unsigned short *func_02099728(void *p);

void func_02011138(unsigned short *dest, unsigned int src)
{
    *dest = *func_020996e0((void *) func_02011368((void *) src));
}

int func_0201111c(void *argument0)
{
    int v = func_02011368((void *) argument0);
    if (v) {
        return func_0209975c(v);
    } else {
        return 0;
    }
}

int func_020110e8(void *argument0)
{
    int r4;
    int r5;

    r4 = func_02011368((void *) argument0);
    r5 = 0x20;
    if (r4 != 0) {
        r5 = func_0209984c((void *) r4);
        if (func_0209975c(r4) != 0) {
            r5 += 0x10;
        }
    }
    if (r5 < 0x20) {
        return r5;
    }
    return 0;
}

void func_020110c4(unsigned short *out, int param)
{
    void *res;
    *out = 0xfff1;
    res = (void *) func_02011368((void *) param);
    if (res) {
        *out = *func_02099728(res);
    }
}
