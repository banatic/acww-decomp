/* func_02016a48 @ 0x02016a48, 0x1b4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Work {
    unsigned char pad_00[0x5c];
    int unk_5C;
    unsigned char pad1[0x64 - 0x60];
    int unk_64;
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;
    unsigned char pad_90[0x94 - 0x90];
    short unk_94;
};

struct UnkStruct_02016a48 {
    int unk_00;
    unsigned char pad1[0x98 - 4];
    unsigned char unk_98;
};

extern void func_0201b188(void *, void *);
extern int func_0201bee0(void *, int *, short *);
extern int FX_MulFunc(int, int);
extern int func_020e8ed8(int, int);
extern int func_0201c3dc(int);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_0201aff4(void *, int);
extern void func_0201b044(void *, void *);
extern void func_0201afd4(void *, void *);
extern unsigned short data_020c80f8;
extern char data_021fbee8[];

void func_02016a48(struct UnkStruct_02016a48 *self, struct Work *work)
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

    func_0201b188((char *) work + 0x350, work);

    if (func_0201bee0(work, coord, &angle) != 0) {
        dx = coord[0] - work->unk_5C;
        dy = coord[2] - work->unk_64;
        sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);

        if (sum == 0) {
            work->unk_94 = work->unk_8E;
            if (angle != work->unk_8E) {
                func_0201b1a4((char *) work + 0x350, work, 3, 0, data_020c80f8);
                func_0201aff4((char *) work + 0x350, angle);
                self->unk_98 = 2;
            } else {
                func_0201b1a4((char *) work + 0x350, work, 0, 0, data_020c80f8);
                func_0201aff4((char *) work + 0x350, angle);
                func_0201b044((char *) work + 0x350, data_021fbee8);
                func_0201afd4((char *) work + 0x350, data_021fbee8);
                self->unk_98 = 0;
            }
        } else {
            if (sum >= 0x29) {
                v = func_020e8ed8(dx, dy);
                if (func_0201c3dc((short) (v - angle)) != 0) {
                    if (self->unk_00 == 2) {
                        func_0201b1a4((char *) work + 0x350, work, 2, 0, data_020c80f8);
                    } else {
                        func_0201b1a4((char *) work + 0x350, work, 1, 0, data_020c80f8);
                    }
                    work->unk_94 = work->unk_8E;
                    func_0201aff4((char *) work + 0x350, angle);
                    self->unk_98 = 1;
                } else {
                    func_0201aff4((char *) work + 0x350, v);
                }
                func_0201b044((char *) work + 0x350, coord);
                func_0201afd4((char *) work + 0x350, coord);
            }
        }
    } else {
        func_0201b1a4((char *) work + 0x350, work, 0, 0, data_020c80f8);
        func_0201aff4((char *) work + 0x350, angle);
        func_0201b044((char *) work + 0x350, data_021fbee8);
        func_0201afd4((char *) work + 0x350, data_021fbee8);
        self->unk_98 = 0;
    }
}