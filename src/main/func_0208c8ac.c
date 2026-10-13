/* func_0208c8ac @ 0x0208c8ac, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xcc];
    int cc;
    int d0;
    int d4;
    int d8;
} UnkStruct_0208c8ac;

extern int func_02039810(void);
extern int func_0208ce88(UnkStruct_0208c8ac *s);
extern void func_020e8bb0(int *p, int a, int b, int c, int d);

void func_0208c8ac(UnkStruct_0208c8ac *s)
{
    int a;
    int b;
    int target;
    int v;

    a = func_02039810();
    b = func_0208ce88(s);
    if (a != 0 && b != 0) {
        target = 0xfffec000;
    } else {
        target = 0;
    }
    s->d4 = s->d4 + 0xa00;
    v = s->d4;
    if (v < 0x2300) {
        v = 0x2300;
    } else if (v > 0x5000) {
        v = 0x5000;
    }
    s->d4 = v;
    if (target != s->d0) {
        if (s->d8 < 0 || b == 0) {
            goto reset;
        }
        s->d8 = s->d8 + 1;
        if (s->d8 > 0xa) {
        reset:
            s->d0 = target;
            s->d8 = 0;
        }
    } else {
        s->d8 = 0;
    }
    func_020e8bb0(&s->cc, s->d0, 0x600, s->d4, 0x2300);
}
