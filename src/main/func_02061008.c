/* func_02061008 @ 0x02061008, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern int func_0204f3e4(int, void *, void *, void *, void *, void *, void *, int, int);
extern void func_0204f800(void *, void *, int, int, int, int);
extern int func_0204bae8(int);
extern int func_0204f538(int, void *, int, int, int);

int func_02061008(int arg1)
{
    struct {
        unsigned short x, y, z;
        unsigned int a, b, c, d, e, f;
        unsigned char pad[0x18];
    } s;
    int a0;

    a0 = func_0204e414();
    s.y = 0x5014;
    s.z = 0x501A;

    if (func_0204f3e4(a0, &s.c, &s.d, &s.e, &s.f, &s.y, &s.z, 1, 0) != 0) {
        func_0204f800(&s.a, &s.b, s.c, s.d, s.e, s.f);
        s.x = (unsigned short) func_0204bae8(arg1);
        if (func_0204f538(a0, &s.x, s.a, s.b, 0) != 0) {
            return 1;
        }
    }
    return 0;
}
