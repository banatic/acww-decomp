/* func_0200a9e0 @ 0x0200a9e0, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct LocalType {
    unsigned int data[12];
};

typedef struct {
    char pad_00[0xc4];
    unsigned int unk_C4;
    unsigned int unk_C8;
    unsigned int unk_CC;
    short unk_D0;
    char pad_D2[0x298 - 0xd2];
    struct LocalType unk_298;
    char pad_2C8[0x2d8 - 0x298 - 0x30];
    unsigned int unk_2D8;
    char pad_2DC[0x698 - 0x2d8 - 4];
    struct LocalType unk_698;
} UnkStruct_0200a9e0;

// c4/c8/cc are volatile to keep them on the stack.
struct SaveAll {
    volatile unsigned int c4, c8, cc;
    struct LocalType s298;
    struct LocalType s698;
};

extern void func_0200ee40(UnkStruct_0200a9e0 *self);
extern void func_0200f650(UnkStruct_0200a9e0 *self, int n);
extern int func_0200faf0(UnkStruct_0200a9e0 *p, int arg2);

void func_0200a9e0(UnkStruct_0200a9e0 *self)
{
    struct SaveAll sv;
    short save_d0;
    unsigned int t;

    {
        unsigned int *p = (unsigned int *) &self->unk_C4;
        sv.c4 = p[0];
        sv.c8 = p[1];
        sv.cc = p[2];
    }
    save_d0 = self->unk_D0;
    sv.s298 = self->unk_298;
    sv.s698 = self->unk_698;

    func_0200ee40(self);
    func_0200f650(self, 0x1000);

    self->unk_C4 = sv.c4;
    self->unk_C8 = sv.c8;
    self->unk_CC = sv.cc;
    self->unk_D0 = save_d0;
    self->unk_298 = sv.s298;
    self->unk_698 = sv.s698;

    t = (self->unk_2D8 << 4) >> 16;
    if (t >= 6) {
        func_0200faf0(self, 0x400);
    }
}
