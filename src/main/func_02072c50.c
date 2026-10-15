/* func_02072c50 @ 0x02072c50, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e98b4(int);
extern void func_020e9898(int);
extern void func_0207225c(void);
extern void func_02072244(int);
extern int func_02072bd0(int, unsigned char);
extern int func_02072da0(void *);
extern int func_02072220(int, int, int);
extern int func_02072260(void);
extern int func_02072268(int, int, int);
extern int func_02072d4c(unsigned int);
extern void func_02072eec(int, int);
extern void func_02072b8c(int);

void func_02072c50(int a, int b)
{
    int r6;
    int tmp;
    short i;

    r6 = func_020e98b4(0x1000);
    if (r6 != 0) {
        if (r6 != 0) {
            func_0207225c();
        }
        func_02072244(r6);
        for (i = 0; i < 8u; i++) {
            tmp = (func_02072220(r6, func_02072da0((void *) func_02072bd0(a, (unsigned char) i)), i), func_02072260());
            func_02072268(tmp, func_02072d4c((unsigned int) func_02072bd0(a, (unsigned char) i)), i);
            func_02072eec(func_02072d4c((unsigned int) func_02072bd0(a, (unsigned char) i)), b);
        }
        func_020e9898(r6);
    }
    func_02072b8c(a + 0x11a0);
}
