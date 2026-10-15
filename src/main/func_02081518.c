/* func_02081518 @ 0x02081518, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082500(void *b);
extern unsigned int *func_02082164(void *local);
extern void *func_0205195c(void *local);
extern int func_02082308(void *local, void *b);
extern void func_02082114(void *local, void *ptr, int n);
extern void *func_0208214c(void *local);
extern void func_020036ec(void *a, void *b, int r7, int d);
extern void func_0207f2f4(void *a, unsigned char v);
extern void func_0207f2e8(void *a, unsigned char v);
extern void *func_0207f1c8(void *a);
extern void func_0209b5f0(void *a, unsigned char *ptr, unsigned char w);
extern void *func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);
extern void func_0207f414(void *a, int r, int zero);
extern void func_0207d634(void *a);
extern void func_0207ef3c(void *a, int c);

void func_02081518(void *a, void *b, int c, int d, unsigned char e)
{
    unsigned char local[0x18];
    int i;
    int res;
    int res2;
    unsigned char v;
    unsigned char v2;
    unsigned short x;
    void *r4;
    int r7;

    r4 = func_02082500(b);
    r7 = 0;

    func_02082164(local);
    if (r4) {
        r7 = ((unsigned char *) r4)[0x4a];
    }
    func_020036ec((char *) a + 0x7a0, b, r7, d);
    func_0205195c(local);
    if (func_02082308(local, b)) {
        func_02082114(local, (char *) a + 0x7c6, 4);
    }

    if (r4) {
        x = *(unsigned short *) ((char *) r4 + 0x2c);
        if (x < 0x100) {
            x = (unsigned short) (x + 0x11a8);
        } else {
            x = 0x11a8;
        }
        *(unsigned short *) ((char *) a + 0x7d2) = x;

        for (i = 0; i < 10; i++) {
            *(unsigned short *) ((char *) a + i * 2 + 0x78c) = *(unsigned short *) ((char *) r4 + i * 2 + 6);
        }

        func_0207f2f4(a, ((unsigned char *) r4)[0x30]);
        func_0207f2e8(a, ((unsigned char *) r4)[0x31]);
        func_0209b5f0(func_0207f1c8(a), (unsigned char *) r4 + 0x32, e);
        res = func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(a)));
        func_0207f414(a, res, 0);
        ((unsigned char *) a)[0x7d8] = ((unsigned char *) r4)[0x2f];
        res2 = func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(a)));
        if (res2 == 2) {
            v = ((unsigned char *) a)[0x7d8];
            v2 = v % 10;
            ((unsigned char *) a)[0x7d8] = v2;
        }
        func_0207d634(a);
        ((unsigned char *) a)[0x7da] = ((unsigned char *) r4)[0x2e];
    }
    func_0207ef3c(a, c);
    func_0208214c(local);
}
