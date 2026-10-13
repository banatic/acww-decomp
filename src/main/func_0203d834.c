/* func_0203d834 @ 0x0203d834, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d540(void *t);
extern void func_0203d4d4(void *t, int v);
extern void func_020a8164(void *t, void *p);
extern void func_0203d4cc(void *t, int v);
extern void func_0203d4c8(void *t, int v);
extern void func_0203d4d0(void *t, int v);
extern void func_0203d668(void *g);
extern int func_0203d564(void *g, void *t);
extern void func_0203d528(void *t);

extern int data_021c69b4;

int func_0203d834(int a, int b, int c, int d, unsigned char *pe, unsigned char *pf, unsigned char *pg, unsigned char *ph,
                  void *pi)
{
    unsigned char buf[0x34];
    int r1, r2, r3, r4, ok;

    func_0203d540(buf);
    func_0203d4d4(buf, 1);
    func_020a8164(buf, pi);

    func_0203d4cc(buf, a);
    func_0203d4c8(buf, d);
    buf[0x1e] = *pe;
    func_0203d4d0(buf, 4);
    func_0203d668(&data_021c69b4);
    r1 = func_0203d564(&data_021c69b4, buf);

    func_0203d4c8(buf, 0);
    func_0203d4cc(buf, b);
    buf[0x1e] = *pf;
    func_0203d4d0(buf, 5);
    func_0203d668(&data_021c69b4);
    r2 = func_0203d564(&data_021c69b4, buf);

    func_0203d4cc(buf, b);
    buf[0x1e] = *pg;
    func_0203d4d0(buf, 6);
    func_0203d668(&data_021c69b4);
    r3 = func_0203d564(&data_021c69b4, buf);

    func_0203d4cc(buf, c);
    buf[0x1e] = *ph;
    func_0203d4d0(buf, 7);
    func_0203d668(&data_021c69b4);
    r4 = func_0203d564(&data_021c69b4, buf);

    ok = r1 && r2 && r3 && r4;
    func_0203d528(buf);
    return ok;
}
