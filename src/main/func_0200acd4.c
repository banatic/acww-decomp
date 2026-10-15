/* func_0200acd4 @ 0x0200acd4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200ad78(void *, void *, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_0200acd4(void *a1, int *a2, int a3, int a4, int a5, short a6)
{
    int a4_save = a4;
    int copy[2];
    char buf1[12];
    char buf2[20];
    int res;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x1a, a5, a6);
    copy[0] = a2[0];
    copy[1] = a2[1];
    func_0200ad78(buf2, copy, a3, a4_save);
    res = func_0200e894(a1, buf1);
    func_0200e91c(buf1);
    return res;
}
