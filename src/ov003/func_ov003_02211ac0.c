/* func_ov003_02211ac0 @ 0x02211ac0, 0x160 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;
struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};
struct UnkStruct_02211ac0_2 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x2d8 - 0x90];
    int unk_2D8;
    char pad2[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct S7d4 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    void *unk_800;
};
struct UnkStruct_02211ac0 {
    short h;
    char pad2[2];
    int sp4;
    int sp8;
    Vec a;
    Vec b;
    Vec c;
    Vec d;
};
extern void func_020912d4(int, void *, void *, int);
extern void func_0200f328(void *, int);
extern void func_0200f27c(void *, int);
extern void func_0200f268(void *, int);
extern void func_ov003_02221294(void *, void *, int);
extern void func_0204f818(int *, int *, void *);
extern void func_02030db8(int, int);
extern void func_ov003_02220f40(void *, void *, short);
extern void func_02010f5c(void *);
void func_ov003_02211ac0(struct UnkStruct_02211ac0_2 *o)
{
    struct UnkStruct_02211ac0 t;
    struct S7d4 *p;
    int x;
    int y;
    int z;
    int *f704_ptr;
    if ((*(&o->unk_704)) != 0x49) {
        p = &o->unk_7D4;
        x = p->unk_04;
        t.a.x = x;
        y = p->unk_08;
        t.a.y = y;
        z = p->unk_0C;
        t.a.z = z;
        t.h = o->unk_8E;
        if ((*(&o->unk_704)) == 0x4b) {
            switch ((int) ((((u32) o->unk_2D8) << 4) >> 16)) {
                case 2:
                    func_020912d4(6, &t.a, 0, 0);
                    break;

                case 5:
                    func_0200f328(o, 0x841);
                    func_0200f27c(o, 9);
                    break;

                case 7:
                    func_020912d4(7, &t.a, &t.h, 0);
                    t.b.x = t.a.x;
                    t.b.y = t.a.y;
                    t.b.z = t.a.z;
                    func_ov003_02221294(o->unk_800, &t.b, 0);
                    func_0200f268(o, 0x1c);
                    func_0204f818(&t.sp4, &t.sp8, &t.a);
                    func_02030db8(t.sp4, t.sp8);
                    break;
            }

        } else {
            switch ((int) ((((u32) o->unk_2D8) << 4) >> 16)) {
                case 5:
                    func_0200f328(o, 0x85b);
                    func_0200f27c(o, 9);
                    break;

                case 12:
                    func_020912d4(6, &t.a, 0, 0);
                    break;

                case 18:
                    func_020912d4(8, &t.a, &t.h, 0);
                    break;

                case 21:
                    t.c.x = x;
                    t.c.y = y;
                    t.c.z = z;
                    func_ov003_02220f40(o->unk_800, &t.c, o->unk_8E);
                    t.d.x = t.a.x;
                    t.d.y = t.a.y;
                    t.d.z = t.a.z;
                    func_ov003_02221294(o->unk_800, &t.d, 0);
                    func_0200f328(o, 0x85c);
                    func_0200f268(o, 0x1c);
                    break;
            }
        }
    }
    func_02010f5c(o);
}
