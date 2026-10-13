/* func_ov003_022171ec @ 0x022171ec, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_022172bc(void *, int, int, unsigned char);
extern int func_0200e894(int, void *);
extern void func_0200e91c(void *);

int func_ov003_022171ec(int p1, int *p2, int *p3, unsigned char *p4, int p5, short p6)
{
    int saved_p1;
    char buf1[12];
    char buf2[20];
    int result;

    saved_p1 = p1;
    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x46, p5, p6);
    func_ov003_022172bc(buf2, *p2, *p3, *p4);
    result = func_0200e894(saved_p1, buf1);
    func_0200e91c(buf1);
    return result;
}
