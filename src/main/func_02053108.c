/* func_02053108 @ 0x02053108, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_02053108;
typedef struct {
    UnkStruct_02053108 e[4];
    unsigned char mask[1];
    unsigned char val[2];
} UnkStruct_02053108_2;

extern int func_02053278(UnkStruct_02053108_2 *t, int a, int b);

int func_02053108(UnkStruct_02053108_2 *t, int a, int b, unsigned int value)
{
    unsigned int i;

    if (value >= 16) {
        return 0;
    }

    if (func_02053278(t, a, b) == -1) {
        for (i = 0; i < 4; i++) {
            if ((((int) t->mask[i >> 3] >> (i & 7)) & 1) == 0) {
                int shift = (i & 1) << 2;
                unsigned int shv;
                t->e[i].lo = a;
                t->e[i].hi = b;
                t->val[i >> 1] &= ~(0x0f << shift);
                shv = value << shift;
                value = shv;
                t->val[i >> 1] |= shv;
                t->mask[i >> 3] |= (1 << (i & 7));
                return 1;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if ((((int) t->mask[i >> 3] >> (i & 7)) & 1) != 0) {
                if (a == t->e[i].lo && b == t->e[i].hi) {
                    int shift = (i & 1) << 2;
                    unsigned int shv;
                    t->val[i >> 1] &= ~(0x0f << shift);
                    shv = value << shift;
                    value = shv;
                    t->val[i >> 1] |= shv;
                    return 1;
                }
            }
        }
    }
    return 0;
}
