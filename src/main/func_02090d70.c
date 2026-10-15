/* func_02090d70 @ 0x02090d70, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090db0(void *);

struct UnkStruct_02090d70_2 {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};
struct Mid {
    struct UnkStruct_02090d70_2 *p;
};
struct UnkStruct_02090d70_3 {
    char pad_00[0x18];
    struct Mid *m;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
};
struct UnkStruct_02090d70 {
    int unk_00;
    int unk_04;
    int unk_08;
};
extern struct UnkStruct_02090d70 *data_021d52d4;

void func_02090d70(struct UnkStruct_02090d70_3 *self)
{
    func_02090db0(self);
    if (data_021d52d4) {
        struct UnkStruct_02090d70 *gp = data_021d52d4;
        self->unk_20 = gp->unk_00 + self->m->p->unk_04;
        self->unk_24 = gp->unk_04 + self->m->p->unk_08;
        self->unk_28 = gp->unk_08 + self->m->p->unk_0C;
    }
}
