/* func_0204d708 @ 0x0204d708, 0x9e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204d8b0(int, int, int);
extern int func_0204d924(int, int);
extern void *func_020e9958(void *, int);
extern void func_020e993c(void *, void *);
extern int func_0204d828(int, void *, int, int, int);

int func_0204d708(int a0, int a1, int a2, int a3, void *a4)
{
    int sp4 = a0;
    int r7 = a2;
    int r6 = a1;
    int sp8 = a3;
    int n = func_0204d8b0(sp4, r7, a3);
    int spc = 0;
    if (r6 != 0 && n > 0 && (n & 3) == 0) {
        if (func_0204d924(sp4, r7) != 0) {
            int sp10 = (int) func_020e9958(a4, n);
            void *p = (void *) sp10;
            if (p != 0) {
                if (func_0204d828(sp4, p, r7, sp8, n) != 0) {
                    int r2 = n >> 2;
                    int r1 = 0;
                    int flag = 0;
                    int ok;
                    unsigned char b2, b3;
                    while (r1 < r2) {
                        b3 = ((unsigned char *) p)[3];
                        ok = flag;
                        b2 = ((unsigned char *) p)[2];
                        if (b2 < 0x10 && b3 < 0x10) {
                            ok = 1;
                        }
                        if (ok != 0) {
                            unsigned short v = *(unsigned short *) p;
                            int idx = ((b3 << 4) + b2) << 1;
                            *(unsigned short *) (r6 + idx) = v;
                        }
                        p = (char *) p + 4;
                        r1++;
                    }
                }
                func_020e993c(a4, (void *) sp10);
                spc = 1;
            }
        }
    }
    return spc;
}
