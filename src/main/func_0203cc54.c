/* func_0203cc54 @ 0x0203cc54, 0xc6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(int a, int n);
extern int func_0204bd08(unsigned short *v);
extern void func_02061b1c(unsigned short *dst, unsigned short *src, int n);
extern int func_0204c2b4(unsigned short *v);
extern int func_020996ac(void *p);
extern int func_0203cdcc(int a, unsigned short *v);
extern int func_0204bcdc(unsigned short *v);
extern int func_0204bc64(unsigned short *v);
extern int func_0204bc50(int a, int b);

int func_0203cc54(int a, int n)
{
    void *p = func_020984e8(a, n);
    unsigned int cnt = 0;
    unsigned short v[6];

    v[0] = (unsigned short) a;
    if (p == 0) {
        return cnt;
    }

    if (func_0204bd08(v)) {
        unsigned int i;

        for (i = 0; i < n; i++) {
            v[1] = (unsigned short) (a + i);
            func_02061b1c(&v[4], &v[1], 1);
            v[1] = v[4];
            if (func_0204c2b4(&v[1])) {
                if (func_0203cdcc(func_020996ac(p), &v[1])) {
                    cnt++;
                }
            }
        }
        return cnt;
    } else {
        int zero;
        int base;
        unsigned int i;

        if (func_0204bcdc(v)) {
            v[2] = (unsigned short) a;
            base = func_0204bc64(&v[2]);
            zero = 0;
            for (i = 0; i < n; i++) {
                v[3] = (unsigned short) func_0204bc50(base + (int) i, zero);
                if (func_0204c2b4(&v[3])) {
                    if (func_0203cdcc(func_020996ac(p), &v[3])) {
                        cnt++;
                    }
                }
            }
        }
        return cnt;
    }
}
