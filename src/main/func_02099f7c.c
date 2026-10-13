/* func_02099f7c @ 0x02099f7c, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *a, int b);
extern void func_02099fe0(void *a);
extern int func_02099734(int a);
extern unsigned short *func_02098f48(int a, int b);
extern int func_02098e74(int a, int b);
extern int func_0204c520(unsigned short *a);

unsigned char func_02099f7c(unsigned short *a, int b)
{
    int x;
    unsigned short *p;
    int i;

    x = func_020984e8(a, b);
    func_02099fe0(a);
    p = func_02098f48(func_02099734(x), 0);

    for (i = 0; i < 15; i++) {
        if (func_02098e74(func_02099734(x), i) != 0) {
            if (func_0204c520(p + i) == b) {
                *a |= (1 << i);
                ((unsigned char *) a)[2]++;
            }
        }
    }
    return ((unsigned char *) a)[2];
}
