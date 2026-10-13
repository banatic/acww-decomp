/* func_ov003_02217378 @ 0x02217378, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void);
extern void func_0203f7d0(int *, int *);
extern int func_020912d4(int, int *, void *, int);
extern void func_02091278(int, int *, void *, int);

typedef struct {
    char pad_00[0x62c];
    int unk_62C, unk_630, unk_634;
    char pad_638[0x1a0];
    int unk_7D8;
} UnkStruct_02217378;

void func_ov003_02217378(UnkStruct_02217378 *self)
{
    int loc[3];
    int *q;
    int a, b, c;
    func_02010f5c();
    q = &self->unk_7D8;
    c = self->unk_634;
    b = self->unk_630;
    a = self->unk_62C;
    loc[0] = a;
    loc[1] = b;
    loc[2] = c;
    func_0203f7d0(loc, loc);
    if (self->unk_7D8 == -1) {
        *q = func_020912d4(0x33, loc, (char *) self + 0x8e, 0);
    } else {
        func_02091278(self->unk_7D8, loc, (char *) self + 0x8e, 0);
    }
}
