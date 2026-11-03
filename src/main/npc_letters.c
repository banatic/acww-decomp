/* npc_letters: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020889a8 @ 0x020889a8, 0xb8 bytes, Thumb
 * func_0208893c @ 0x0208893c, 0x6c bytes, Thumb
 * func_02088810 @ 0x02088810, 0x12c bytes, Thumb
 */

extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern void func_02066694(void *);
extern int func_020644cc(int);
extern void func_0209df64(void *);
extern int func_0209767c(int, int);
extern int func_02099870(void *);
extern void func_02066024(void *, void *, void *, void *, void *, int);
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern unsigned short func_02065ed0(void *, int, int);
extern void func_02063cc8(void *);
extern int func_020979f0(void *, int);
extern void func_02098fd0(void *, int);
extern void func_02066688(void *);
extern char data_020e1ff0[];
extern char data_020e1f58[];
extern unsigned char data_020e1f68[];
extern unsigned char data_020e1fdc[];
extern unsigned char data_020e1f60[];
extern void *func_020b5630(void *);
extern void *func_02094fd4(void *);
extern void *func_02099670(void *);
extern unsigned int func_02088a74(void *);
extern int func_020b45d0(void *, unsigned int, int, int, int, int);
extern int func_0203d7c4(int, void *);
extern void *func_02094fbc(void *);
extern void *func_020b5618(void *);

void func_020889a8(void)
{
    void *p;
    unsigned char a[8];
    unsigned char c[0x10c];
    int v;

    p = func_020984e8();
    if (p == 0) {
        return;
    }
    if (func_02099020(p, 0x36) == 0) {
        return;
    }

    func_02066694(&c[8]);

    a[0] = 0;
    a[0] = (unsigned char) func_020644cc(3);
    func_0209df64(&a[4]);
    a[1] = (unsigned char) func_0209767c(3, a[5]);

    v = func_02099870(p);

    func_02066024(&c[8], a, data_020e1ff0, data_020e1f58, &a[1], v);
    func_02063ccc(c, 0, 0x1b);
    func_020638d4(&a[2], c, 0, 0, 1, 1, 0);
    func_02065ed0(&c[8], *(unsigned short *) &a[2], 1);
    func_02063cc8(c);

    if (func_020979f0(&c[8], 0) != 0) {
        func_02098fd0(p, 0x36);
    }

    func_02066688(&c[8]);
}

int func_0208893c(int a0, int a1, unsigned short *a2)
{
    unsigned int ok;
    int t;
    int r;
    unsigned char c;
    int buf[0x40];
    func_02066694(buf);
    c = 0;
    t = (int) func_020984e8();
    c = (unsigned char) a1;
    r = func_02099870((void *) t);
    func_02066024(buf, (void *) (&c), data_020e1fdc, data_020e1f60, data_020e1f68, r);
    func_02065ed0(buf, *a2, 1);
    if (func_020979f0(buf, 0) != 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    func_02066688(buf);
    return ok;
}

void func_02088810(void *boss)
{
    unsigned short arr[3];
    unsigned int buf1[0x10];
    unsigned char buf2[0x24];
    int param;
    void *obj;
    void *vo;
    int p;
    unsigned int count;
    func_020b5630(buf1);
    obj = func_020984e8();
    func_02094fd4(buf2);
    vo = func_02099670(obj);
    if (func_02099020(obj, 0x17)) {
        if (func_02099020(obj, 0x19)) {
            arr[0] = 0x1492;
            p = func_020644cc(2);
            if (func_0208893c((int) boss, p, arr)) {
                func_02098fd0(obj, 0x19);
            }
        }
        if (func_02099020(obj, 0x1a)) {
            arr[1] = 0x1492;
            p = func_020644cc(2);
            p += 2;
            if (func_0208893c((int) boss, p, &arr[1])) {
                func_02098fd0(obj, 0x1a);
            }
        }
    }
    if (func_02099020(obj, 0x18)) {
        if (func_02088a74(vo) >= 1) {
            func_020b45d0(buf1, func_02088a74(vo), 10, 0, 0, 0);
            func_0203d7c4(3, buf1);
            p = func_020644cc(2);
            param = p + 4;
            count = func_02088a74(vo);
            if (count >= 10) {
                count = 10;
                param = 6;
            }
            func_020b45d0(buf1, count * 100, 10, 0, 0, 0);
            func_0203d7c4(4, buf1);
            arr[2] = count + 0x1491;
            if (func_0208893c((int) boss, param, &arr[2])) {
                ((unsigned char *) boss)[0xf] = 0;
            }
        }
    }
    func_02094fbc(buf2);
    func_020b5618(buf1);
}
