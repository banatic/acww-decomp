/* func_ov144_02299968 @ 0x02299968, 0x98 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299968 {
    char pad_00[0xA0];
    unsigned int p;
    char pad_A4[0x14];
    short d;
    char pad_BA[0x07];
    unsigned char b;
    char pad_C2[0x02];
    unsigned int q;
};

extern int func_ov002_02209eec(unsigned int *ptr);

int func_ov144_02299968(struct UnkStruct_02299968 *s)
{
    int n;
    int v;
    int tmp;
    int x;

    n = s->d;
    if (n == 0) {
        return 0;
    }
    if (n > 9) {
        n = 9;
    }

    v = func_ov002_02209eec(&s->q);
    if (v < 0x20) {
        v = 0x20;
    }
    if (v >= 0xA0) {
        v = 0x9F;
    }

    tmp = s->p & 0xF;
    x = (v - (0x20 - tmp)) >> 4;
    if (x >= n) {
        x = n - 1;
    }
    s->b = (unsigned char) x;

    if (tmp != 0) {
        if (x == 0) {
            s->p -= (unsigned int) tmp;
        } else if (x == n - 1) {
            s->b = (unsigned char) (s->b - 1);
            s->p += 0x10u - (s->p & 0xF);
        }
    }

    return 1;
}
