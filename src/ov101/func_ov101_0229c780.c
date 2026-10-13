/* func_ov101_0229c780 @ 0x0229c780, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a08c(void *, void *, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov101_0229c780(unsigned char *p)
{
    void *r4 = func_ov002_02208ae4(p + 0x2300);
    int r2 = func_ov002_02208ad8(p + 0x2300, *(unsigned char *) (p + 0xb8));
    func_ov002_0220a08c(p + 0x229c, r4, r2, 2);
    *(unsigned char *) (p + 0xb6) = *(unsigned char *) (p + 0x8d);
    func_ov002_02208098(p, 10);
}
