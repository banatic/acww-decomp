/* func_020993b4 @ 0x020993b4, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099a28(void *);
extern void *func_02099734(void *);
extern unsigned char *func_02098f48(void *, int);
extern unsigned char *func_02099640(void *);
extern void *func_0209ad9c(unsigned char *, int);
extern void func_0209b56c(void *);
extern void func_0209af04(unsigned char *);
extern int func_02098e8c(void *, int);
extern int func_02098f0c(void *, unsigned char *, int, int);
extern unsigned char *func_020996ac(void *);
extern int func_0203cd2c(unsigned int, unsigned char *, unsigned int, int);
extern unsigned char *func_02098e44(void *, int);
extern int func_02065ec0(unsigned char *);
extern void func_02066650(unsigned char *);

void func_020993b4(void *param)
{
    void *p1;
    unsigned char *p2;
    int i;

    if (func_02099a28(param) == 0) {
        return;
    }

    p1 = func_02099734(param);
    p2 = func_02098f48(p1, 0);

    func_0209b56c((void *) func_0209ad9c(func_02099640(param), 0));
    func_0209b56c((void *) func_0209ad9c(func_02099640(param), 1));
    func_0209af04(func_02099640(param) + 0xa4);

    {
        int val2 = 0;
        int val3 = 0;

        for (i = 0; i < 15; i++) {
            if (func_02098e8c(p1, i) == 2) {
                int cond = val2;
                unsigned short val = *(unsigned short *) p2;
                if ((unsigned int) val >= 0x11a8u && (unsigned int) val <= 0x12a7u) {
                    cond = 1;
                }
                if (cond) {
                    func_02098f0c(p1, p2, i, 1);
                    func_0203cd2c((unsigned int) func_020996ac(param), p2, (unsigned int) val3, 1);
                }
            }
            p2 += 2;
        }
    }

    p2 = func_02098e44(p1, 0);
    for (i = 0; i < 10; i++) {
        if ((unsigned char) (func_02065ec0(p2) + 0xf9) <= 1) {
            func_02066650(p2);
        }
        p2 += 0x100;
    }
}
