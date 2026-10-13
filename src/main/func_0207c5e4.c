/* func_0207c5e4 @ 0x0207c5e4, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x4050];
    long long a;
    long long b;
} UnkStruct_0207c5e4;

extern int func_0207cad4(void);
extern int func_0209dffc(long long *v);
extern int func_0209e3ac(void *p1, long long *v, int k);
extern int func_0209e380(long long *v, void *p1);
extern int func_020644cc(int n);

int func_0207c5e4(UnkStruct_0207c5e4 *s, void *p1)
{
    int n;
    int ok;

    if (func_0207cad4() < 8) {
        if (s->b == 0) {
            if (s->a == 0 || func_0209dffc(&s->a) != 0) {
                return 1;
            }
            if (func_0209e3ac(p1, &s->a, 0x3f) == 1) {
                if (func_0209e380(&s->a, p1) >= 1) {
                    return 1;
                }
            }
        } else if (func_0209e3ac(p1, &s->b, 0x3f) == 1) {
            n = func_0209e380(&s->b, p1);
            if (n > 0) {
                if (n >= 8) {
                    ok = 1;
                } else if (func_020644cc(8 - n) == 0) {
                    ok = 1;
                } else {
                    ok = 0;
                }
                if (ok != 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    }
    return 0;
}
