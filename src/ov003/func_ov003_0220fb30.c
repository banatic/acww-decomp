/* func_ov003_0220fb30 @ 0x0220fb30, 0x4e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_0220fb80(void *, int, int, int, unsigned char);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_ov003_0220fb30(int a1, int a2, int a3, int a4, unsigned char a5, int a6, short a7)
{
    char buf1[12];
    char buf2[16];
    int result;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x68, a6, a7);
    func_ov003_0220fb80(buf2, a2, a3, a4, a5);
    result = func_0200e894(a1, buf1);
    func_0200e91c(buf1);
    return result;
}
