/* func_0201dcbc @ 0x0201dcbc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};

extern struct Pair data_020d91d0;
extern int func_020154b4(int p1, unsigned short *p2, int p3, int p4, int p5);
extern void func_0202dbf0(int p1, struct Pair p2);

void func_0201dcbc(int param)
{
    unsigned short buf;
    buf = 0x3818;
    func_020154b4(param, &buf, 0, 5, 0);
    func_0202dbf0(param, data_020d91d0);
}
