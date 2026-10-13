/* func_0205cba8 @ 0x0205cba8, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205cd4c(int, int);
extern int func_0205ccfc(int, int);
extern int func_0205cd58(int, int);
extern void MI_CpuCopy8(int, int, int);
extern void func_0205cd40(int, int, int);
extern void func_0205ccf0(int, int, int);

extern unsigned char data_021c9b58[];

void func_0205cba8(unsigned char *p, int n)
{
    unsigned char b;
    int v6, v7, a, b2;

    b = *p;
    if (n == b) {
        return;
    }
    v6 = func_0205cd4c((unsigned int) data_021c9b58, n);
    if (v6 == func_0205cd4c((unsigned int) data_021c9b58, b)) {
        return;
    }
    v7 = func_0205ccfc((unsigned int) data_021c9b58, n);
    if (v7 == 0) {
        return;
    }
    a = func_0205cd58((unsigned int) data_021c9b58, n);
    b2 = func_0205cd58((unsigned int) data_021c9b58, b);
    if (a == 0 || b2 == 0) {
        return;
    }
    MI_CpuCopy8(a, b2, v7);
    func_0205cd40((unsigned int) data_021c9b58, b, v6);
    func_0205ccf0((unsigned int) data_021c9b58, b, v7);
}
