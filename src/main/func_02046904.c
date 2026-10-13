/* func_02046904 @ 0x02046904, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

union Stamp {
    int w[2];
    struct {
        unsigned short f0;
        unsigned char f2, f3, f4, f5, f6, f7;
    } unk_00;
};

struct Pair {
    union Stamp a;
    union Stamp b;
};

extern int func_0206f7a4(void);
extern void func_0209e474(union Stamp *);
extern int func_0209e350(union Stamp *, union Stamp *);
extern const unsigned char data_021f39fc[3];

int func_02046904(void)
{
    int result;

    result = 0;
    if (func_0206f7a4() != 0) {
        result = 1;
    } else {
        struct Pair p;

        p.a.w[0] = 0;
        p.a.w[1] = 0;
        p.b.w[0] = 0;
        p.b.w[1] = 0;

        func_0209e474(&p.a);

        {
            unsigned char *dp = (unsigned char *) data_021f39fc;
            p.b.w[0] = 0;
            p.b.w[1] = 0;
            p.b.unk_00.f5 = dp[2];
            p.b.unk_00.f4 = dp[1];
            p.b.unk_00.f3 = dp[0];
            p.b.unk_00.f2 = 6;
        }

        if (func_0209e350(&p.a, &p.b) > 0) {
            result = 1;
        }
    }
    return result;
}
