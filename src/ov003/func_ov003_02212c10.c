/* func_ov003_02212c10 @ 0x02212c10, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02212d04(void *, unsigned char, unsigned char, unsigned char);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_ov003_02212c10(int a1, unsigned char *p2, unsigned char *p3, unsigned char *p4, int a5, short a6)
{
    int saved_a1 = a1;
    int result;
    char local1[12];
    char local2[20];

    func_0200e92c(local1);
    func_0200e90c(local1, 0x59, a5, a6);
    func_ov003_02212d04(local2, *p2, *p3, *p4);
    result = func_0200e894(saved_a1, local1);
    func_0200e91c(local1);
    return result;
}
