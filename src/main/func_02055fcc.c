/* func_02055fcc @ 0x02055fcc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_021054e4(void *, int);
extern void MTX_Identity43_(void *);

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[2];
    char unk_08[0x54];
    int unk_5C;
    int unk_60;
    char unk_64[0x30];
    int unk_94;
} UnkStruct_02055fcc;

void func_02055fcc(UnkStruct_02055fcc *self)
{
    func_021054e4(self->unk_08, 0);
    self->unk_5C = 0;
    self->unk_60 = 0;
    MTX_Identity43_(self->unk_64);
    self->unk_04 = 0;
    self->unk_94 = 0;
}
