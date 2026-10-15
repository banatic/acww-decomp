/* func_ov004_0223bf40 @ 0x0223bf40, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    char pad_00[0x5c];
    Vec pos;
} Player;
typedef struct {
    char pad_00[0x7b8];
    Vec pos;
} UnkStruct_0223bf40;
extern Player *func_020961a8(int);
extern void *func_ov004_0223ce84(void);
extern UnkStruct_0223bf40 *func_ov004_0223cd58(void *, unsigned int);
extern int func_ov004_022111f0(UnkStruct_0223bf40 *);
extern long long func_01ffd028(const Vec *, const Vec *);
extern unsigned int func_ov004_0223c130(void);
extern void *func_ov004_022168e4(UnkStruct_0223bf40 *);
extern int data_ov004_022595d8;

void func_ov004_0223bf40(void *receiver)
{
    Player *pl = func_020961a8(4);
    if (pl != 0) {
        Vec me;
        int besti;
        unsigned int i;
        int best;
        int d;
        Vec *q;
        q = &pl->pos;
        me.x = q->x;
        me.y = q->y;
        me.z = q->z;
        i = 0;
        besti = -1;
        best = data_ov004_022595d8;
        for (; i < func_ov004_0223c130(); i++) {
            UnkStruct_0223bf40 *o = func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (o != 0 && func_ov004_022111f0(o) != 0) {
                Vec p;
                Vec tmp = o->pos;
                p.x = tmp.x;
                p.y = tmp.y;
                p.z = tmp.z;
                d = (int) func_01ffd028(&p, &me);
                if (d < best) {
                    besti = i;
                    best = d;
                }
            }
        }
        if (besti != -1) {
            UnkStruct_0223bf40 *o = func_ov004_0223cd58(func_ov004_0223ce84(), besti);
            if (o != 0) {
                func_ov004_022168e4(o);
            }
        }
    }
}
