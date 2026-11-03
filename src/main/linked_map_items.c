/* linked_map_items: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205fa84 @ 0x0205fa84, 0xa2 bytes, Thumb
 * func_0205fa40 @ 0x0205fa40, 0x44 bytes, Thumb
 * func_0205f9d4 @ 0x0205f9d4, 0x6c bytes, Thumb
 */

extern int func_02077898(unsigned char *);
extern void func_02077a34(unsigned char *, unsigned char *, unsigned char *);
extern int func_020b6674(unsigned char);
extern int func_0204e414(void);
extern int func_0204df08(unsigned char);
extern int func_0204f538(int, void *, int, int, int);
extern void func_0204f380(int, int, int);
extern int func_0204f31c(int, int, int);
extern int func_02073d90(void *p);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, int a, int b);
extern void func_02073770(void *p, int a, int b);
extern int *data_020ccf94;
extern void func_020778b0(void *buf, int param3);
extern void func_02077a54(void *p, int a, unsigned char b);
extern int func_020a7278(void);

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

void func_0205fa40(int arg)
{
    if (func_0205fa84((unsigned char *) arg) && func_02073d90(data_020ccf94)) {
        int *p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, arg, 5);
        func_02073770(p, 0x12, 4);
    }
}

void func_0205f9d4(unsigned char p0, unsigned char p1, int p2, int p3, int p4)
{
    unsigned char buf[8];
    int flag;

    func_020778b0(buf, p3);

    flag = (p4 != 0) ? 1 : 0;

    func_02077a54(buf + 2, p2, flag);

    buf[3] = p0;
    buf[4] = p1;

    if (func_020a7278()) {
        func_0205fa40((int) buf);
    } else {
        void *base = (*(void * *) &data_020ccf94);
        func_02073820(base);
        func_020737f0(base, (int) buf, 5);
        func_02073770(base, 0x13, 6);
    }
}
