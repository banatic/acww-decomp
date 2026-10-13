/* func_020bce60 @ 0x020bce60, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int tag;
    char pad[0x5c];
    unsigned int bits;
    char pad_64[0x10];
} Entry;

typedef struct {
    char pad[0x14d8];
    Entry arr[13];
} Container;

int func_020bce60(Container *base, int val)
{
    int res = 1;
    Entry *p = base->arr;
    Entry *end = base->arr + 13;
    int zero = 0;
    int mask3 = 3;
    while (p < end) {
        if (p->tag == 9) {
            unsigned int t = p->bits;
            int low = (t >> 8) & mask3;
            int high = (t >> 29) & 1;
            int x = high ? 1 : zero;
            if (low == val || x == 0) {
                res = 0;
                break;
            }
        }
        p++;
    }
    return res;
}
