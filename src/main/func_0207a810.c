/* func_0207a810 @ 0x0207a810, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(char *p);
extern int func_02099870(int x);
extern int func_020951bc(int x);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_020807a8(char *p, int x);
extern int func_02081898(int x);
extern int func_0207f270(char *p);
extern int func_020794d8(int x);
extern int func_0207cc54(int a, int b, int c);

int func_0207a810(char *p)
{
    int ret;
    int v;
    unsigned char flags;
    int count;
    int i;

    ret = func_020984e8(p);
    if (ret != 0) {
        v = func_02099870(ret);
    } else {
        v = 0;
    }

    if (v == 0) {
        goto fail;
    }
    if (func_020951bc(v) == 0) {
        goto fail;
    }

    flags = 0;
    count = 0;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) && func_020807a8(p, v) != 0 && func_02081898(func_020807a8(p, v)) == 0 &&
            func_020794d8(func_0207f270(p)) == 0) {
            flags |= (1 << i);
            count++;
        }
        p += 0x7ec;
    }

    return func_0207cc54(flags, count, 8);

fail:
    return -1;
}
