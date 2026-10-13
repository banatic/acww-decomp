/* func_0207deb4 @ 0x0207deb4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned short *func_0207dfd4(void *, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);

int func_0207deb4(void *a0, unsigned short *b)
{
    unsigned short *p;
    int i;
    unsigned int ok1;
    unsigned int ok2;
    unsigned int t;
    p = func_0207dfd4(a0, 0);
    i = 0;
    ok1 = 0;
    ok2 = 0;
    for (; i < 4; p++, i++) {
        if (func_0204bcdc(b) != 0) {
            if (func_0204bc64(b) == func_0204bc64(p)) {
                t = 1;
            } else {
                t = ok1;
            }
        } else {
            if (*b == *p) {
                t = 1;
            } else {
                t = ok2;
            }
        }
        if (t > 0) {
            return i;
        }
    }
    return -1;
}
