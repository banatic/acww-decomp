/* func_02072a58 @ 0x02072a58, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e98b4(int size);
extern void func_020e9898(void *p);
extern void func_0207221c(void);
extern void func_02072204(void *p);
extern int func_02072a48(void *self, unsigned char idx);
extern int func_02072da0(void *);
extern int func_02072d4c(int x);
extern int func_020721e0(void *p, int a, int b);
extern int func_02072260(void);
extern int func_02072268(int a, int b, int c);
extern void *func_02072ee8(void *record);
extern void *func_02095040(void *record);
extern void func_02064290(int a, int b);
extern void func_020950cc(int a, int b);

extern unsigned short data_020ccb64;
extern unsigned short data_020d1858;

void func_02072a58(void *self)
{
    void *p;
    short i;
    unsigned short g1, g2;
    int tmp;

    p = (void *) func_020e98b4(0x1000);
    if (p == 0) {
        return;
    }
    if (p != 0) {
        func_0207221c();
    }
    func_02072204(p);

    g1 = data_020ccb64;
    g2 = data_020d1858;

    for (i = 0; (unsigned) i < 8; i++) {
        tmp = (func_020721e0(p, (func_02072da0((void *) func_02072a48(self, (unsigned char) i))), i), func_02072260());
        func_02072268(tmp, func_02072d4c(func_02072a48(self, (unsigned char) i)), i + 8);
        func_02064290((int) func_02095040(func_02072ee8((void *) func_02072d4c(func_02072a48(self, (unsigned char) i)))), g1);
        func_020950cc((int) func_02072ee8((void *) func_02072d4c(func_02072a48(self, (unsigned char) i))), g2);
    }

    func_020e9898(p);
}
