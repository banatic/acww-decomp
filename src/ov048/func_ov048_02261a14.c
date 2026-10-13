/* func_ov048_02261a14 @ 0x02261a14, 0x24 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(void *a, char *b, void *c);
extern void *data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02261a14;

void func_ov048_02261a14(UnkStruct_02261a14 *self, int cond)
{
    if (cond == 0) {
        char local = 0x59;
        func_0206844c(self->unk_40, &local, data_ov048_02263d20);
    }
}
