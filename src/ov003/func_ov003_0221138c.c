/* func_ov003_0221138c @ 0x0221138c, 0x1a4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern void func_020912d4(int a, void *b, int c, int d);
extern void func_0200f328(void *self, int a);
extern void func_0200f27c(void *self, int a);
extern void func_0200f268(void *self, int a);
extern void func_0204f818(int *a, int *b, void *v);
extern void func_02030db8(int a, int b);
extern void func_ov003_02221294(int a, void *b, unsigned char c);
extern void func_0200ee40(void *self);
extern void func_0200f650(void *self, int a);
extern void func_0203f7d0(void *a, void *b);

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} Mtx;
typedef struct {
    Vec3 v;
    unsigned char c0;
    unsigned char c1;
} S7d4;

typedef struct {
    char pad_00[0xc4];
    Vec3 v;
    short d0;
    char pad_D2[0x298 - 0xd2];
    Mtx a;
    char pad_2C8[0x2d8 - 0x2c8];
    unsigned int unk_2D8;
    char pad_2DC[0x62c - 0x2dc];
    Vec3 unk_62C;
    char pad_638[0x698 - 0x638];
    Mtx b;
    char pad_6C8[0x704 - 0x6c8];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    S7d4 s;
    char pad_7E4[0x800 - 0x7e4];
    int unk_800;
    char pad_804[0x824 - 0x804];
    Vec3 unk_824;
} UnkStruct_0221138c;

void func_ov003_0221138c(UnkStruct_0221138c *self)
{
    int a, b;
    Vec3 loc;
    volatile Vec3 sv;
    Mtx sa, sb;
    Vec3 copy;
    short d;
    S7d4 *q;
    int tx, ty, tz;
    Vec3 *p;

    func_02010f5c(self);
    if (self->unk_704 == 0x49) {
        return;
    }
    q = &self->s;
    loc.x = q->v.x;
    loc.y = q->v.y;
    loc.z = q->v.z;
    switch ((self->unk_2D8 << 4) >> 16) {
        case 5:
            func_020912d4(6, &loc, 0, 0);
            break;
        case 6:
            func_0200f328(self, 0x841);
            func_0200f27c(self, 9);
            break;
        case 0xc:
            func_020912d4(8, &loc, 0, 0);
            func_0204f818(&a, &b, &loc);
            func_02030db8(a, b);
            copy.x = loc.x;
            copy.y = loc.y;
            copy.z = loc.z;
            func_ov003_02221294(self->unk_800, &copy, q->c1);
            func_0200f27c(self, 0xd);
            func_0200f268(self, 0x1c);
            break;
    }
    if (((self->unk_2D8 << 4) >> 16) >= 0x18) {
        func_0200f268(self, 9);
        p = &self->v;
        sv.x = self->v.x;
        sv.y = p->y;
        sv.z = p->z;
        d = self->d0;
        sa = self->a;
        sb = self->b;
        func_0200ee40(self);
        func_0200f650(self, 0x1000);
        self->v.x = sv.x;
        self->v.y = sv.y;
        self->v.z = sv.z;
        self->d0 = d;
        self->a = sa;
        self->b = sb;
    } else {
        tz = self->unk_62C.z;
        ty = self->unk_62C.y;
        tx = self->unk_62C.x;
        self->unk_824.x = tx;
        self->unk_824.y = ty;
        self->unk_824.z = tz;
        func_0203f7d0(&self->unk_824, &self->unk_824);
    }
}
