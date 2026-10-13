/* func_02016f30 @ 0x02016f30, 0x16c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Work {
    unsigned char pad_00[0x5c];
    int unk_5C;
    unsigned char pad1[0x64 - 0x60];
    int unk_64;
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;
};

struct UnkStruct_02016f30 {
    int unk_00;
    unsigned char pad1[0x98 - 4];
    unsigned char unk_98;
};

extern int func_0201bee0(void *, int *, short *);
extern int FX_MulFunc(int, int);
extern int func_020e8ed8(int, int);
extern int func_0201c3dc(int);
extern int func_0201b1a0(void *);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_0201aff4(void *, int);
extern void func_0201b044(void *, void *);
extern void func_0201afd4(void *, void *);
extern unsigned short data_020c80f8;
extern char data_021fbee8[];

void func_02016f30(struct UnkStruct_02016f30 *self, struct Work *work)
{
    int coord[3];
    short angle;
    int dx, dy;
    int sum;
    int v;

    coord[0] = 0;
    coord[1] = 0;
    coord[2] = 0;
    angle = work->unk_8E;

    if (func_0201bee0(work, coord, &angle) == 0) {
        return;
    }
    dx = coord[0] - work->unk_5C;
    dy = coord[2] - work->unk_64;
    sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);
    if (sum < 0x29) {
        if (angle != work->unk_8E) {
            func_0201b1a4((char *) work + 0x350, work, 3, 0, data_020c80f8);
            func_0201aff4((char *) work + 0x350, angle);
            self->unk_98 = 2;
            return;
        }
        if (func_0201b1a0((char *) work + 0x350) == 0) {
            return;
        }
        func_0201b1a4((char *) work + 0x350, work, 0, 0, data_020c80f8);
        func_0201b044((char *) work + 0x350, data_021fbee8);
        func_0201afd4((char *) work + 0x350, data_021fbee8);
        return;
    }
    v = func_020e8ed8(dx, dy);
    if (func_0201c3dc((short) (v - angle)) != 0) {
        if (self->unk_00 == 2) {
            func_0201b1a4((char *) work + 0x350, work, 2, 0, data_020c80f8);
        } else {
            func_0201b1a4((char *) work + 0x350, work, 1, 0, data_020c80f8);
        }
        func_0201aff4((char *) work + 0x350, angle);
        self->unk_98 = 1;
    } else {
        func_0201b1a4((char *) work + 0x350, work, 4, 0, data_020c80f8);
        func_0201aff4((char *) work + 0x350, v);
        self->unk_98 = 3;
    }
    func_0201b044((char *) work + 0x350, coord);
    func_0201afd4((char *) work + 0x350, coord);
}
