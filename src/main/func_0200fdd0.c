/* func_0200fdd0 @ 0x0200fdd0, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80bc;

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_02043d84(int a, int *pos, int c, int d, int k);
extern int func_0200fea0(void *s);

struct Vec {
    int x;
    int z;
};

// 12-byte object; the callee gets a pointer to its second word. The first word is never written.
struct Loc {
    int unk_00;
    int x;
    int z;
};

struct UnkStruct_0200fdd0 {
    char pad_00[0x800];
    int unk_800;
    char pad_804[8];
    int unk_80C;
    char pad_810[8];
    int unk_818;
    char pad_81C[4];
    unsigned short unk_820;
    unsigned short unk_822;
};

int func_0200fdd0(struct UnkStruct_0200fdd0 *s, struct Vec *v, int c, int d)
{
    unsigned short *o;
    int cx;
    int cz;
    int x;
    int z;
    struct Loc loc;

    if (s->unk_80C == -1) {
        x = v->x;
        z = v->z;
        cx = x >> 4;
        cz = z >> 4;
        o = func_0204f5e0(data_021c80bc, cx, cz, x - (cx << 4), z - (cz << 4), 0);
        if (o == 0) {
            s->unk_822 = 0xfff1;
            s->unk_820 = s->unk_822;
            return 2;
        }
        s->unk_822 = *o;
        s->unk_820 = s->unk_822;
        loc.x = v->x;
        loc.z = v->z;
        s->unk_80C = func_02043d84(s->unk_800, &loc.x, c, d, 0xfff1);
        if (s->unk_80C == -1) {
            return 0;
        }
        s->unk_818 = func_0200fea0(s);
        switch (s->unk_818) {
            case 0:
                return 1;
            case 2:
                return 0;
        }
        return 3;
    }
    return 1;
}
