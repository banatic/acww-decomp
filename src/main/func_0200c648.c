/* func_0200c648 @ 0x0200c648, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_0200c648;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char pad_5C[0x8e - 0x5c];
    short unk_8E;
    unsigned char pad_90[0x2d0 - 0x90];
    int unk_2D0;
    unsigned char pad_2D4[0x6c8 - 0x2d4];
    int fAx, fAy, fAz;
    int fBx, fBy, fBz;
} UnkStruct_0200c648_2;

extern void func_02010f5c(void);
extern int func_02056f28(void *flags, int bit);
extern void func_020912d4(int type, void *a, void *b, int c);

void func_0200c648(UnkStruct_0200c648_2 *self)
{
    short h;
    UnkStruct_0200c648 v;
    short f8e;

    func_02010f5c();

    if (func_02056f28(&self->unk_2D0, 0xd)) {
        func_020912d4(0x22, (char *) self + 0x5c, 0, 0);
        return;
    }

    if (!func_02056f28(&self->unk_2D0, 3)) {
        return;
    }

    f8e = self->unk_8E;

    v.x = self->fBx;
    v.y = self->fBy;
    v.z = self->fBz;
    v.z = v.z + 0x266;
    h = f8e + 0xaf0;
    func_020912d4(0x27, &v, &h, 0);

    v.x = self->fAx;
    v.y = self->fAy;
    v.z = self->fAz;
    v.z = v.z + 0x266;
    h = f8e - 0xaf0;
    func_020912d4(0x27, &v, &h, 0);
}
