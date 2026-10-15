/* func_ov109_0229c564 @ 0x0229c564, 0x70 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(void *p, void *q, int n);
extern int func_ov109_0229cbd4(unsigned char *a, unsigned char b);
extern int func_ov109_0229cb9c(unsigned char *a, unsigned char b);
extern void func_ov002_02209874(void *p, void *q);
extern void func_ov002_02209910(void *p, int v, int w);
extern void func_ov002_0220970c(void *p, int n);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov109_0229c564(unsigned char *a, int flag)
{
    int v;
    int w;

    func_ov002_02208c58(a + 0x22d8, a + 0x26c0, 0);
    v = func_ov109_0229cbd4(a, a[0x29d4]);
    w = func_ov109_0229cb9c(a, a[0x29d4]);
    if (flag) {
        func_ov002_02209874(a + 0x22d8, a + 0x218c);
    } else {
        func_ov002_02209910(a + 0x22d8, v, w);
    }
    func_ov002_0220970c(a + 0x22d8, 0);
    func_ov002_02208098(a, 0xb);
}
