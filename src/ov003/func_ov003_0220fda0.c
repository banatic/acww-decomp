/* func_ov003_0220fda0 @ 0x0220fda0, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(int *);
extern void func_0200e90c(int *, int, int, int);
extern void func_0204f7e0(int *, int);
extern int func_0200e894(int, int *);
extern void func_0200e91c(int *);
extern void func_ov003_0220fdf4(int *, int *);

int func_ov003_0220fda0(int p1, int p2, int p3, int p4)
{
    int buf[3];
    int out[4];
    int vec1[3];
    int vec2[3];
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x67, p3, p4);
    func_0204f7e0(vec1, p2);

    vec2[0] = vec1[0];
    vec2[1] = vec1[1];
    vec2[2] = vec1[2];

    func_ov003_0220fdf4(out, vec2);

    ret = func_0200e894(p1, buf);
    func_0200e91c(buf);

    return ret;
}
