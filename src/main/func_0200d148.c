/* func_0200d148 @ 0x0200d148, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(void *a, int b, int c, int d);
extern int func_0200fbe0(void *a);
extern void func_0205eae0(void *a, int b, int c, int d);
extern void func_0200d198(void *a);

void func_0200d148(void *a, void *b, int previous)
{
    unsigned char *q = (unsigned char *) b + 0xc;
    unsigned int *p = (unsigned int *) ((char *) a + 0x7d4);
    int three = 3;

    func_020109fc(a, 1, three, three);
    if (func_0200fbe0(a) == 4) {
        func_0205eae0((char *) a + 0x5a0, 1, three, 0);
    }
    func_0200d198(p);
    if (*q) {
        *p = 0x456;
    }
}
