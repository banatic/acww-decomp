/* func_0203776c @ 0x0203776c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int key;
    int pad_04;
    int pad_08;
    int value;
    char pad_10[32];
} BigEntry;

typedef struct {
    int key;
    int value;
} SmallEntry;

typedef struct {
    BigEntry big[31];
    SmallEntry small[9];
} Cache;

extern int func_020377d8(int key, int global);
extern int data_021c9b24;

int func_0203776c(Cache *cache, int key)
{
    unsigned int i, j;
    int v = 0;
    int val;
    BigEntry *b;
    SmallEntry *e;

    b = cache->big;
    for (i = 0; i < 31; b++, i++) {
        if (b->key == key) {
            v = b->value;
            break;
        }
    }

    e = cache->small;
    for (j = 0; j < 9; e++, j++) {
        val = e->value;
        if (val == 0) {
            if (v != 0) {
                e->key = key;
                e->value = v;
            } else {
                e->value = func_020377d8(key, data_021c9b24);
                e->key = key;
            }
            return e->value;
        } else {
            if (e->key == key) {
                return val;
            }
        }
    }
    return 0;
}
