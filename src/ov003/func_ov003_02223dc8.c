/* func_ov003_02223dc8 @ 0x02223dc8, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};

extern unsigned char *func_0204cab4(void);
extern void func_0204f794(void *a4, int a5, int a6);
extern unsigned char data_ov003_02236b88[];

void func_ov003_02223dc8(unsigned char *a0, int *p1, int *p2, int *p3, void *a4, unsigned short *a5, struct Pair *a6)
{
    unsigned char *base = func_0204cab4();
    int flag = 0;
    unsigned short val = *a5;
    int t;

    if (val >= 0x26 && val <= 0x2a) {
        flag = 1;
    }

    if (flag || (val >= 0x2b && val <= 0x2e) || val == 0x67) {
        t = (a6->a ^ a6->b) & 1;
        *p2 = 0;
        p1[4] = t;
        *p3 = 0x22;
        t = t * 23;
        if (*(&data_ov003_02236b88[t] + (unsigned int) base) != 0) {
            *p3 = 0x24;
        }
    } else if ((val >= 0x5d && val <= 0x61) || (val >= 0x62 && val <= 0x65) || val == 0x6d || val == 0x6b) {
        *p2 = 1;
        p1[4] = 3;
        *p3 = 0x25;
    } else if ((val >= 0xc8 && val <= 0xcf) || (val >= 0xd0 && val <= 0xd3)) {
        *p2 = 2;
        p1[4] = 3;
        *p3 = 0x27;
    } else {
        *p2 = 0;
        p1[4] = 2;
        *p3 = 0x22;
    }

    func_0204f794(a4, a6->a, a6->b);
}