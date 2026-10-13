/* func_ov003_02212968 @ 0x02212968, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct Vec {
    int x, y, z;
};
struct Vec2 {
    int x, y;
};
struct Blk {
    struct Vec v;
    short unk_0C;
    short unk_0E;
};
struct UnkStruct_02212968 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x2d0 - 0x9c];
    char unk_2D0[0x704 - 0x2d0];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct Blk unk_7D4;
};

extern "C" int func_02056f94(void *);
extern "C" void func_020109fc(struct UnkStruct_02212968 *, int, int, int);
extern "C" int func_ov003_02212574(struct UnkStruct_02212968 *, struct Vec *, int);
extern "C" void func_0204f818(int *, int *, struct Vec *);
extern "C" void func_ov003_02212830(struct UnkStruct_02212968 *, struct Vec2 *, int, int);

extern "C" void func_ov003_02212968(struct UnkStruct_02212968 *o)
{
    struct Blk *bp = &o->unk_7D4;
    if (func_02056f94(o->unk_2D0) == 0 && o->unk_704 != 0x4a) {
        return;
    }
    if (o->unk_704 == 0x49) {
        func_020109fc(o, 0x4a, 3, 0);
    }
    if (o->unk_98 != 0) {
        return;
    }
    if (bp->unk_0C != o->unk_8E) {
        return;
    }
    struct Vec2 p;
    struct Vec2 q;
    struct Vec a;
    struct Vec b;
    a = bp->v;
    b = a;
    int ok = (func_ov003_02212574(o, &b, 1) == 0);
    if (!ok) {
        return;
    }
    p.x = 0;
    p.y = 0;
    func_0204f818(&p.x, &p.y, &a);
    q.x = p.x;
    q.y = p.y;
    func_ov003_02212830(o, &q, 6, ~0);
}