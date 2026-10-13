/* func_0204e108 @ 0x0204e108, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204e204(void *out, int a, int b, int c, int d, int e, int f, int g);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);

int func_0204e108(int a0, int a1, int a2, int a3)
{
    struct {
        unsigned short x;
        unsigned short y;
    } s;
    int r;

    func_0204e204(&s, a0, a1, a2, a3, 0x5014, 0x501a, 1);
    if (func_0204bcdc(&s) != 0) {
        s.y = 0xfff1;
        if (func_0204bc64(&s) == func_0204bc64(&s.y)) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (s.x == 0xfff1) {
            r = 1;
        } else {
            r = 0;
        }
    }
    return !r;
}
