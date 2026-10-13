/* func_ov118_0229b4d8 @ 0x0229b4d8, 0x58 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229b630(void *);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_ov118_0229b46c(void *, int, unsigned char);
extern void func_02070a04(int, int, int);

void func_ov118_0229b4d8(void *p, unsigned char *q)
{
    int x = 0;
    int y = 0;
    int i;
    for (i = 0; i < 13; i++) {
        int r = func_ov118_0229b630(p);
        func_02070adc(r, 6, 0x160 + i * 16, 8, 1, 0xf, x);
        func_ov118_0229b46c(p, r, q[i]);
        func_02070a04(r, y, y);
    }
}
