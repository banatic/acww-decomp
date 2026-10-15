/* func_ov068_02274abc @ 0x02274abc, 0x88 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *unused0);
extern void func_021074dc(int, int);
extern void func_ov068_022749dc(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);

typedef struct {
    char pad_00[0xec];
    char unk_EC[1];
    char pad_ED[0x148 - 0xec - 1];
    int unk_148;
    char pad_14C[0x334 - 0x148 - 4];
    char unk_334[1];
    char pad_335[0x4e8 - 0x334 - 1];
    int unk_4E8;
    char pad_4EC[0x730 - 0x4e8 - 4];
    int unk_730;
} UnkStruct_02274abc;

int func_ov068_02274abc(UnkStruct_02274abc *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    if (self->unk_730 == 7) {
        func_021074dc(self->unk_148, 3);
    }
    func_ov068_022749dc(self, 0);
    self->unk_4E8 |= 2;
    if (self->unk_730 == 3) {
        func_02016764((void *) self->unk_334, (void *) self, 0x142, 0, 0, 0x1000, 0, 1);
        func_02054188(&self->unk_EC, 0xc, 0xe);
    }
    return 1;
}
