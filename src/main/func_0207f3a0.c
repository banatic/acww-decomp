/* func_0207f3a0 @ 0x0207f3a0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Key {
    int a;
    int b;
} Key;
typedef struct Entry {
    u16 id;
    u8 unk_02;
    u8 unk_03;
} Entry;

extern int func_0207ff58(void *ctx, volatile u16 *id);

int func_0207f3a0(void *ctx, Key *key, Entry *e, int n)
{
    volatile u16 id;
    int i;
    unsigned int seed;
    int ka;
    int kb;

    if (e != 0) {
        kb = key->b;
        ka = key->a;
        if ((unsigned int) ka < 0x10 && (unsigned int) kb < 0x10) {
            seed = 0;
            for (i = 0; i < n; e++, i++) {
                if (key->a != e->unk_02) {
                    continue;
                }
                if (key->b != e->unk_03) {
                    continue;
                }
                id = e->id;
                {
                    unsigned int ok = seed;
                    u16 hi = id;
                    u16 lo = id;
                    if (lo >= 0xf000 && hi <= 0xf02f) {
                        ok = 1;
                    }
                    if (ok > 0) {
                        return func_0207ff58(ctx, &id);
                    }
                }
            }
        }
    }
    return -1;
}
