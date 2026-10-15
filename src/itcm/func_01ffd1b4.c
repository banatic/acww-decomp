/* func_01ffd1b4 @ 0x01ffd1b4, 0x230 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_01ffd1b4 {
    u8 pad_00[0xc];
    u16 shown;
    u16 want;
} UnkStruct_01ffd1b4;

typedef struct Node {
    u8 pad_00[0xc];
    struct Node *next;
    void *obj;
} Node;

typedef struct Work {
    u8 pad_00[0xe];
    u8 state;
    u8 dirty;
    u8 flagA;
    u8 flagB;
    u8 pad_12;
    u8 bits;
    u8 pad_14[0x18 - 0x14];
    Node *list;
    u8 pad_1C[0x28 - 0x1c];
    UnkStruct_01ffd1b4 a;
    UnkStruct_01ffd1b4 b;
} Work;

extern int data_021fd004, data_021fd024, data_021fd014, data_021fd034;

extern int func_020e8ce0(void *g, UnkStruct_01ffd1b4 *s);
extern int func_020e8c70(void *g, UnkStruct_01ffd1b4 *s);
extern int func_020e8ca8(void *g, UnkStruct_01ffd1b4 *s);
extern int func_020ee8a8(void *g, UnkStruct_01ffd1b4 *s);
extern void func_020ee470(void *obj);
extern Work *func_020ee45c(Work *w);

int func_01ffd1b4(Work *w)
{
    Node *n;
    Work *o;
    unsigned int b;
    UnkStruct_01ffd1b4 *sub;

    if (w->dirty) {
        w->dirty = 0;
        b = (w->state == 1);
        if (b > 0) {
            func_020e8ce0(&data_021fd004, &w->a);
            func_020e8ce0(&data_021fd024, &w->b);
        } else {
            func_020e8ce0(&data_021fd014, &w->a);
        }
        func_020e8c70(&data_021fd034, &w->a);
        w->state = 2;
        for (n = w->list; n != 0; n = n->next) {
            func_020ee470(n->obj);
        }
    } else {
        o = func_020ee45c(w);
        if (o != 0) {
            if ((o->bits & 1) || (o->bits & 2)) {
                w->bits |= 2;
            } else if (w->bits & 2) {
                // ROM rereads the byte after the masked test destroys its value.
                w->bits = *(volatile u8 *) &w->bits & ~2;
            }
            if ((o->bits & 4) || (o->bits & 8)) {
                w->bits |= 8;
            } else if (w->bits & 8) {
                w->bits = *(volatile u8 *) &w->bits & ~8;
            }
        }
        b = (w->state == 1);
        if (b > 0) {
            sub = &w->a;
            b = (sub->want != sub->shown);
            if (b > 0) {
                func_020e8ce0(&data_021fd004, &w->a);
                sub = &w->a;
                sub->shown = sub->want;
                func_020ee8a8(&data_021fd004, &w->a);
            }
            sub = &w->b;
            b = (sub->want != sub->shown);
            if (b > 0) {
                func_020e8ce0(&data_021fd024, &w->b);
                sub = &w->b;
                sub->shown = sub->want;
                func_020ee8a8(&data_021fd024, &w->b);
            }
        } else {
            b = (w->state == 2);
            if (b == 0) {
                if (w->flagB) {
                    w->flagB = 0;
                    func_020e8ca8(&data_021fd014, &w->a);
                } else if (w->flagA) {
                    w->flagA = 0;
                    func_020ee8a8(&data_021fd004, &w->a);
                    func_020ee8a8(&data_021fd024, &w->b);
                    w->state = 1;
                }
            }
        }
    }
    return 1;
}
