/* func_02084598 @ 0x02084598, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[2];
    short unk_02;
} UnkStruct_02084598;

extern void *data_021c80bc;
extern int func_0204f490(void *, int *, int *, int *, int *, unsigned short *, unsigned short *, int, int);
extern void func_0204f800(int *, int *, int, int, int, int);
extern void func_0204f794(void *, int, int);
extern int func_020644cc(int);

int func_02084598(void *unused, void *p1, UnkStruct_02084598 *p2)
{
    unsigned short h[2];
    int a, b, c, d;
    int e, f;
    void *ctx;

    ctx = data_021c80bc;
    if (ctx != 0) {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        h[0] = 0x5014;
        h[1] = 0x501a;
        if (func_0204f490(ctx, &a, &b, &c, &d, &h[0], &h[1], 1, 0) != 0) {
            e = 0;
            f = 0;
            func_0204f800(&e, &f, a, b, c, d);
            e += 2;
            f += 2;
            func_0204f794(p1, e, f);
            p2->unk_02 = func_020644cc(0xffff);
            return 1;
        }
    }
    return 0;
}
