/* func_0204e188 @ 0x0204e188, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204e204(void *s, int a, int b, int c, int d, int e, int f, int g);
extern int func_0204bcdc(void *s);
extern int func_0204bc64(void *p);

int func_0204e188(int param1, int param2, int param3, int param4)
{
    struct {
        unsigned short a;
        unsigned short b;
    } s;
    int result;

    func_0204e204(&s, param1, param2, param3, param4, 0x5000, 0x5000, 0x200);
    if (func_0204bcdc(&s)) {
        s.b = 0xfff1;
        result = (func_0204bc64(&s) == func_0204bc64(&s.b));
    } else {
        result = (s.a == 0xfff1);
    }
    return !result;
}
