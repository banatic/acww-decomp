/* card_save_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a15ac @ 0x020a15ac, 0x7c bytes, Thumb
 * func_020a1518 @ 0x020a1518, 0x94 bytes, Thumb
 * func_020a145c @ 0x020a145c, 0xbc bytes, Thumb
 */

extern int func_020984d4(void);
extern int func_02098844(char *, int);
extern void *func_02099664(int);
extern int func_02077bb8(void *);
extern int func_020508fc(void *, int, int);
extern void func_02077bc0(void *, int);
extern int func_02050af8(char *, char *, void *, int);
extern char data_021dc7bc[];
extern char data_021dc7a8[];
extern char data_021c8188[];
extern char *data_020d1c20[2];
extern int func_020984e8(void);
extern char *func_02099658(int);
extern void *func_02077c9c(char *p);
extern void func_02077ca8(char *p, void *q);
extern unsigned char data_020e37f8;
extern int data_021ee418;
extern int data_021f37f4;
extern int func_0209015c(int);
extern void func_02090168(int, int);
extern int func_0208ffe8(int);
extern void func_0208fff4(int, int);

int func_020a15ac(void)
{
    int t1 = func_020984d4();
    int t2 = func_02098844(data_021dc7bc, t1);
    void *ptr = func_02099664(t2);
    int x = func_02077bb8(ptr);
    int y = func_020508fc(ptr, 0x50, x);
    func_02077bc0(ptr, y);
    {
        int off = (char *) ptr - data_021dc7a8;
        if (func_02050af8(data_021c8188, data_020d1c20[0] + off, ptr, 0x50) == 1) {
            return 1;
        }
        if (func_02050af8(data_021c8188, data_020d1c20[1] + off, ptr, 0x50) == 1) {
            return 1;
        }
        return 0;
    }
}

int func_020a1518(void)
{
    char *base = data_021dc7a8; // hold in callee-saved register
    int val;
    char *b, *c;
    int diff;

    val = func_020984d4();
    b = func_02099658((int) func_020984e8());
    if (val >= 4) {
        val = data_020e37f8;
    }
    c = func_02099658((int) func_02098844(base + 0x14, val));
    func_02077ca8(b, (void *) func_020508fc((void *) b, 0x484, (int) (func_02077c9c(b))));
    diff = c - base;
    if (func_02050af8(data_021c8188, data_020d1c20[0] + diff, (void *) b, 0x484) == 1) {
        return 1;
    }
    if (func_02050af8(data_021c8188, data_020d1c20[1] + diff, (void *) b, 0x484) == 1) {
        return 1;
    }
    return 0;
}

int func_020a145c(void)
{
    volatile char pad[4];
    unsigned int a, b, d1, d2;
    d1 = (unsigned int) &data_021ee418 - (unsigned int) ((int *) data_021dc7a8);
    d2 = (unsigned int) &data_021f37f4 - (unsigned int) ((int *) data_021dc7a8);
    func_02090168((int) &data_021ee418,
                  func_020508fc((void *) ((int) &data_021ee418), 0x950, func_0209015c((int) &data_021ee418)));
    func_0208fff4((int) &data_021f37f4,
                  func_020508fc((void *) ((int) &data_021f37f4), 0x104, func_0208ffe8((int) &data_021f37f4)));
    a = ((int *) data_020d1c20)[0];
    if (func_02050af8((char *) ((int) ((int *) data_021c8188)), (char *) (a + d1), (void *) ((int) &data_021ee418), 0x950) ==
        1) {
        return 1;
    }
    b = ((int *) data_020d1c20)[1];
    if (func_02050af8((char *) ((int) ((int *) data_021c8188)), (char *) (b + d1), (void *) ((int) &data_021ee418), 0x950) ==
        1) {
        return 1;
    }
    if (func_02050af8((char *) ((int) ((int *) data_021c8188)), (char *) (a + d2), (void *) ((int) &data_021f37f4), 0x104) ==
        1) {
        return 1;
    }
    if (func_02050af8((char *) ((int) ((int *) data_021c8188)), (char *) (b + d2), (void *) ((int) &data_021f37f4), 0x104) ==
        1) {
        return 1;
    }
    return 0;
}
