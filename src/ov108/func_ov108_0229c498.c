/* func_ov108_0229c498 @ 0x0229c498, 0x70 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208c58(void *p, void *q, int n);
extern int func_ov108_0229cc20(unsigned char *a, unsigned char b);
extern int func_ov108_0229cbe4(unsigned char *a, unsigned char b);
extern void func_ov002_02209874(void *p, void *q);
extern void func_ov002_02209910(void *p, int v, int w);
extern void func_ov002_0220970c(void *p, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov108_0229c498(unsigned char *a, int flag)
{
    int v;
    int w;

    func_ov002_02208c58(a + 0x24fc, a + 0x28e4, 0);
    v = func_ov108_0229cc20(a, a[0x2b1]);
    w = func_ov108_0229cbe4(a, a[0x2b1]);
    if (flag) {
        func_ov002_02209874(a + 0x24fc, a + 0x23b0);
    } else {
        func_ov002_02209910(a + 0x24fc, v, w);
    }
    func_ov002_0220970c(a + 0x24fc, 0);
    func_ov002_02208098((void *) (a), 0x13);
}
