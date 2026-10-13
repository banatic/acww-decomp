/* func_0204dfe0 @ 0x0204dfe0, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204e204(unsigned short *buf, int a, int *b, int *c, int *d, int e, int f, int g);
extern int func_0204bcdc(unsigned short *buf);
extern int func_0204bc64(unsigned short *p);

int func_0204dfe0(int a0, int *a1, int *a2, int *a3)
{
    unsigned short buf[2];
    int result;

    func_0204e204(buf, a0, a1, a2, a3, 0x5000, 0x5000, 0x200);

    if (func_0204bcdc(buf) != 0) {
        buf[1] = 0xfff1;
        if (func_0204bc64(buf) == func_0204bc64(&buf[1])) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (buf[0] == 0xfff1) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result == 0) {
        *a1 -= 0x2000;
        a1[2] += 0x8000;
        if (a2) {
            (*a2)--;
        }
        if (a3) {
            (*a3) += 4;
        }
        return 1;
    } else {
        return 0;
    }
}
