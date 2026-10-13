/* func_ov096_0229d1d4 @ 0x0229d1d4, 0x94 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229c2fc(void *, int);
extern void func_ov002_02208c58(void *, void *, int);
extern int func_ov096_0229f290(void *, int);
extern int func_ov096_0229f200(void *, int);
extern void func_ov002_022098ec(void *, int, int);
extern void func_ov002_02209874(void *, void *, int);
extern void func_ov002_02209910(void *, int, int);
extern void func_ov002_0220970c(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov096_0229d1d4(unsigned char *p, int flag)
{
    int result1;
    int a, b;

    result1 = func_ov096_0229c2fc(p, 0x40000);
    func_ov002_02208c58(p + 0x2564, p + 0x294c, result1);

    a = func_ov096_0229f290(p, p[0xb6]);
    b = func_ov096_0229f200(p, p[0xb6]);

    if (p[0xb6] == 0x25) {
        b = 0x68;
        func_ov002_022098ec(p + 0x2564, b, b);
    } else if (flag != 0) {
        func_ov002_02209874(p + 0x2564, p + 0x2418, b);
    } else {
        func_ov002_02209910(p + 0x2564, a, b);
    }

    func_ov002_0220970c(p + 0x2564, 0);
    func_ov002_02208098(p, 0x1d);
}
