/* func_02039c4c @ 0x02039c4c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x34];
    int unk_44;
    char pad_48[0x60];
    int unk_A8;
    char pad_AC[0x4];
    int unk_B0;
} UnkStruct_02039c4c;

extern int func_0209d368(int id, int index);
extern int func_020e895c(void *, int, int);
extern void func_02039c0c(UnkStruct_02039c4c *);

void func_02039c4c(UnkStruct_02039c4c *self)
{
    int r2;

    if (self->unk_0C == 0) {
        r2 = func_0209d368(0x137, 3) + 6;
    } else {
        r2 = func_0209d368(0x12d, 3) + 6;
    }
    func_020e895c((char *) self + 0x48, self->unk_44, r2);
    self->unk_A8--;
    if (self->unk_A8 <= 0) {
        self->unk_B0 = 0;
    }
    if (self->unk_B0 == 0) {
        func_02039c0c(self);
    }
}
