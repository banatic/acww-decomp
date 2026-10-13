/* func_02032cac @ 0x02032cac, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short key[2];
    unsigned char count;
    unsigned char pad_05[3];
    int a[2];
    int b[2];
} PairSet;

int func_02032cac(PairSet *s, short key, int val, int other)
{
    short *k = s->key;
    int *v = s->b;
    int i;

    for (i = 0; i < s->count; i++) {
        if (*k == key && *v == val) {
            return 0;
        }
        k++;
        v++;
    }
    if (s->count < 2) {
        s->key[s->count] = key;
        s->b[s->count] = val;
        s->a[s->count] = other;
        s->count++;
        return 1;
    }
    return 0;
}
