/* func_02087a78 @ 0x02087a78, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct byteflags {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char f2 : 2;
    unsigned char f4 : 2;
    unsigned char : 2;
};
struct UnkStruct_02087a78 {
    int unk_00;
    int pad_04;
    int unk_08;
};
struct Vec3 {
    int y;
    int z;
    int x;
};
typedef struct {
    int unk_00;
    int unk_04;
} Pair;
extern Pair data_020d06ec[];
extern short data_020d06e4[];
extern int data_021ebcd2;
extern void func_02087b30(void *p);
extern void func_0204f7e0(void *a, void *b);
extern int func_020871a8(void *a);
extern int func_02087178(void *a);

void func_02087a78(struct byteflags *p0, void *p1, short *out, struct UnkStruct_02087a78 *p3)
{
    struct Vec3 tmp;
    int x, y;
    Pair *e;

    if (!p0->bit1) {
        func_02087b30(p0);
    }

    e = &data_020d06ec[p0->f2];
    x = p3->unk_08 + e->unk_04;
    y = p3->unk_00 + e->unk_00;

    tmp.y = y;
    tmp.z = 0;
    tmp.x = x;

    func_0204f7e0(p1, &tmp);

    if (func_020871a8(&data_021ebcd2) >= 5) {
        *out = data_020d06e4[p0->f2];
    } else {
        if (func_02087178(&data_021ebcd2) != 0) {
            *out = 0;
        } else {
            *out = (p0->f4) << 14;
        }
    }
}
