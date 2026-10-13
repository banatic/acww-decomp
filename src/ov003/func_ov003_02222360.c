/* func_ov003_02222360 @ 0x02222360, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(void *, int, int);
extern void func_020044c0(void *, int, int, int);

typedef struct {
    int x, y;
} UnkStruct_02222360;
typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x32];
    int unk_3C, unk_40, unk_44;
    char pad_48[0x18];
    char sub[4];
} UnkStruct_02222360_2;

void func_ov003_02222360(UnkStruct_02222360_2 *self, UnkStruct_02222360 *p)
{
    unsigned int ok;
    int id;
    unsigned short a, b;
    volatile unsigned short v[8];

    func_0204f794((char *) self + 0x18, p->x, p->y);
    ok = 0;
    self->unk_3C = 0;
    self->unk_40 = 0;
    self->unk_44 = 0;
    id = 0x813;
    v[0] = 0xfff1;
    v[0] = self->unk_08;
    a = v[0];
    b = v[0];
    if (b >= 0xa7 && a <= 0xc6) {
        ok = 1;
    }
    if (ok > 0) {
        id = 0x7f0;
    }
    func_020044c0((char *) self + 0x60, id, 0x7f, 0);
}
