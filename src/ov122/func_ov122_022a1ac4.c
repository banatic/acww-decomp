/* func_ov122_022a1ac4 @ 0x022a1ac4, 0x60 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229c208(void *p, unsigned int bank);
extern void func_020029e8(int a, int b);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int v);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov122_022a1738(void *p);
extern void func_ov122_0229efd8(void *p, int v);
extern int func_ov002_02207f60(void *p);

void func_ov122_022a1ac4(char *p)
{
    func_ov095_0229c208(p + 0xc0, 6);
    func_020029e8(6, 1);
    func_ov002_02207f20(p, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov122_022a1738(p);
    func_ov122_0229efd8(p, 1);
    *(int *) (p + 0x94) = func_ov002_02207f60(p);
    *(unsigned char *) (p + 0x8c) = 0xb;
}
