/* func_0205fa84 @ 0x0205fa84, 0xa2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077898(unsigned char *);
extern void func_02077a34(unsigned char *, unsigned char *, unsigned char *);
extern int func_020b6674(unsigned char);
extern int func_0204e414(void);
extern int func_0204df08(unsigned char);
extern int func_0204f538(int, void *, int, int, int);
extern void func_0204f380(int, int, int);
extern int func_0204f31c(int, int, int);

int func_0205fa84(unsigned char *arg)
{
    unsigned char buf[8];
    int v7;
    int flag;
    signed char x, y;

    v7 = func_02077898(arg);
    func_02077a34(arg + 2, buf, buf + 1);
    flag = buf[1] != 0;
    x = (signed char) arg[3];
    y = (signed char) arg[4];

    if (func_020b6674(buf[0]) != 0) {
        int h;
        h = func_0204e414();
        if (h == 0) {
            goto fail;
        }
        *(unsigned short *) (buf + 2) = (unsigned short) v7;
        func_0204f538(h, buf + 2, x, y, 0);
        if (flag) {
            func_0204f380(h, x, y);
        } else {
            func_0204f31c(h, x, y);
        }
        return 1;
    } else {
        int h;
        h = func_0204df08(buf[0]);
        if (h == 0) {
            goto fail;
        }
        *(unsigned short *) (buf + 4) = (unsigned short) v7;
        func_0204f538(h, buf + 4, x, y, 0);
        return 1;
    }

fail:
    return 0;
}
