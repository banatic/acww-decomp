/* func_ov099_0229c4a0 @ 0x0229c4a0, 0x5c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cd70(void *p, int b);
extern int func_ov099_0229cd1c(void *p, int b);
extern void func_ov002_02208c58(void *a, void *b, int c);
extern void func_ov002_02209910(void *a, int b, int c);
extern void func_ov002_0220970c(void *a, int b);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);

void func_ov099_0229c4a0(unsigned char *p)
{
    int v1;
    int v2;

    func_ov002_02208c58(p + 0x22d8, p + 0x26c0, 0);
    v1 = func_ov099_0229cd70(p, p[0x2908]);
    v2 = func_ov099_0229cd1c(p, p[0x2908]);
    func_ov002_02209910(p + 0x22d8, v1, v2);
    func_ov002_0220970c(p + 0x22d8, 0);
    func_ov002_02208098(p, 0x11);
}
