/* func_02082904 @ 0x02082904, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct VT VT;
typedef struct {
    VT *vt;
} Ob;
struct VT {
    char pad_00[0xa8];
    int (*unk_A8)(Ob *);
};
typedef struct {
    Ob *obj;
    int unk_04;
} UnkStruct_02082904;
typedef struct {
    UnkStruct_02082904 ent[8];
} UnkStruct_02082904_2;

extern int func_02082b60(UnkStruct_02082904_2 *, UnkStruct_02082904 *);
extern int func_020644cc(int);

Ob *func_02082904(UnkStruct_02082904_2 *self, int *outIdx)
{
    Ob *found;
    int n, i;
    UnkStruct_02082904 *e;

    n = 0;
    found = 0;

    for (i = 0; i < 8; i++) {
        e = &self->ent[i];
        if (func_02082b60(self, e) != 0) {
            if (e->obj->vt->unk_A8(e->obj) != 0) {
                n++;
            }
        }
    }
    if (n > 0) {
        n = func_020644cc(n);
        for (i = 0; i < 8; i++) {
            e = &self->ent[i];
            if (func_02082b60(self, e) != 0) {
                if (e->obj->vt->unk_A8(e->obj) != 0) {
                    if (n == 0) {
                        found = e->obj;
                        if (outIdx != 0) {
                            *outIdx = i;
                        }
                        break;
                    }
                    n--;
                }
            }
        }
    }
    return found;
}
