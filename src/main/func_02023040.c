/* func_02023040 @ 0x02023040, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02023040 {
    u8 id;
    u8 unk_01;
    u8 unk_02;
};
struct Node {
    struct UnkStruct_02023040 *items;
    u8 cnt;
    u8 pad_05[3];
};

extern u8 data_020d9f74[];

extern int func_0209a478(int);
extern int func_02015dd4(void *, void *, u8 *, void *, u8 *);

void func_02023040(void *p0, int kind, u16 *pid, int p3, struct Node **list, void *p5)
{
    int key;
    int res;
    struct Node **pp;
    struct Node *p;
    struct UnkStruct_02023040 *q;
    int j;
    unsigned int ok;
    int i;
    unsigned int id;
    int k;
    u8 buf[2];

    pp = list;
    res = (u8) kind;
    if (pp == 0) {
        goto done;
    }
    ok = 0;
    id = *pid;
    if (id >= 0x12e8 && id <= 0x131f) {
        ok = 1;
    }
    if (ok == 0) {
        goto done;
    }
    if (p3 > 1) {
        goto done;
    }
    if (id >= 0x12e8 && id <= 0x131f) {
        key = id - 0x12e8;
    } else {
        key = -1;
    }
    for (i = 0; i < 3; pp++, i++) {
        p = *pp;
        if (p == 0) {
            continue;
        }
        for (j = 0; j < 2; p++, j++) {
            q = p->items;
            if (q == 0) {
                continue;
            }
            for (k = 0; k < p->cnt; q++, k++) {
                if (q->id == key && func_0209a478(q->unk_02) <= 1) {
                    break;
                }
            }
            if (p->cnt < k) {
                break;
            }
        }
        if (j == 2) {
            break;
        }
    }
    if (i == 3) {
        res = 3;
    }
done:
    buf[0] = (u8) res;
    buf[1] = 0;
    func_02015dd4(p0, p5, &buf[0], data_020d9f74, &buf[1]);
}
