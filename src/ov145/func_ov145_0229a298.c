/* func_ov145_0229a298 @ 0x0229a298, 0x48 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a58c(void *p, int unused1, int unused2);
extern void func_ov002_0220a574(void *p);

typedef struct {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
} UnkStruct_0229a298;

int func_ov145_0229a298(UnkStruct_0229a298 *self, int unused, int delta)
{
    if (func_ov002_0220a58c((char *) self + 0x12c, unused, delta)) {
        self->unk_AC = self->unk_A8 - delta;
        func_ov002_0220a574((char *) self + 0x12c);
        self->unk_B0 = self->unk_A8;
        return 1;
    } else {
        return 0;
    }
}
