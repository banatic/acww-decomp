/* func_0204df68 @ 0x0204df68, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e328(void *p1, int a, int b, void *p2, void *p3, int c, int d, int e);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);

int func_0204df68(int a, int b)
{
    unsigned short buf[2];
    void *p2;
    void *p3;
    int result;

    func_0204e328(buf, a, b, &p2, &p3, 0x5020, 0x5020, 0);

    if (func_0204bcdc(buf)) {
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

    return (result == 0) ? 1 : 0;
}
