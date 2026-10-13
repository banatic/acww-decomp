/* func_02037eec @ 0x02037eec, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Src3 {
    int x;
    int y;
    int z;
};

struct Src2 {
    int a;
    int b;
};

struct UnkStruct_02037eec {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int x;
    int y;
    int z;
};

extern void func_02037f28(int, int, int *, int);

void func_02037eec(int a, int b, struct Src3 *s, int d, int t0, int t1, int t2, int t3, struct Src2 *p, int t4)
{
    struct UnkStruct_02037eec local;

    local.x = s->x;
    local.y = s->y;
    local.z = s->z;

    local.unk_00 = t0;
    local.unk_04 = t1;
    local.unk_08 = t2;
    local.unk_0C = t3;

    local.unk_10 = p->a;
    local.unk_14 = p->b;

    local.unk_18 = t4;

    func_02037f28(a, b, &local.x, d);
}
