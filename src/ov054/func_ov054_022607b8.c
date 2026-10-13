/* func_ov054_022607b8 @ 0x022607b8, 0x34 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *ptr;
    int unk_04;
    int unk_08;
} TableEntry;

extern TableEntry data_ov054_02262fac[];
extern void func_0206844c(int, char *, void *);

struct UnkStruct_022607b8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    char *unk_B0;
};

void func_ov054_022607b8(struct UnkStruct_022607b8 *self)
{
    char local = 0x16;
    func_0206844c(self->unk_40, &local, data_ov054_02262fac[*(int *) (self->unk_B0 + 0x808)].ptr);
}
