/* func_ov003_02212830 @ 0x02212830, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02212878(void *, void *);
extern void *func_0200e894(void *, void *);
extern void func_0200e91c(void *);

void *func_ov003_02212830(void *arg0, int *arg1, int arg2, int arg3)
{
    int buf1[2];
    unsigned char buf2[12];
    unsigned char buf3[16];
    void *result;

    func_0200e92c(buf2);
    func_0200e90c(buf2, 0x5a, arg2, arg3);
    buf1[0] = arg1[0];
    buf1[1] = arg1[1];
    func_ov003_02212878(buf3, buf1);
    result = func_0200e894(arg0, buf2);
    func_0200e91c(buf2);
    return result;
}
