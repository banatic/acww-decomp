/* func_020542e0 @ 0x020542e0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Object {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[0x14E];
    int *unk_154;
    int unk_158;
    int unk_15C;
    int unk_160;
    char pad_164[12];
    int unk_170;
    char pad_174[56];
    int unk_1AC;
    int unk_1B0;
};

extern void func_02054860(struct Object *);
extern int func_02056e84(int *);
extern void func_02056ffc(int *);
extern void func_02054170(struct Object *);

void func_020542e0(struct Object *self)
{
    func_02054860(self);
    if (self->unk_1AC != 0 || self->unk_1B0 != 0) {
        if (func_02056e84(&self->unk_170) != 0 && (self->unk_04 & 0x8000) != 0) {
            func_02054170(self);
            self->unk_04 &= ~0x8000;
        }
        func_02056ffc(&self->unk_158);
        *self->unk_154 = self->unk_160;
    }
}
