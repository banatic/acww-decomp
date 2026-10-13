/* func_02068e78 @ 0x02068e78, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void FS_InitFile(void *);
extern int func_02069068(int, void *, int);
extern int func_02069004(int, void *);
extern int func_02068fa0(int, void *);
extern void func_02068f2c(int, int, unsigned char);
extern void func_02068ee4(int, int);

int func_02068e78(int a, int b, int c, int d, unsigned char e)
{
    int saved_d;
    unsigned char buf[0x48];
    int ret = 0;
    int flag;

    saved_d = d;
    flag = (c == 0 && b == 0);

    FS_InitFile(buf);
    if (func_02069068(a, buf, flag) == 0) {
        goto fail;
    }
    if (func_02069004(a, buf) == 0) {
        goto fail;
    }
    if (func_02068fa0(a, buf) == 0) {
        goto fail;
    }

    if (flag) {
        func_02068f2c(a, saved_d, e);
    } else {
        func_02068ee4(a, b);
    }

    ret = 1;

fail:
    return ret;
}
