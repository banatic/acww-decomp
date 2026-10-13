/* func_ov048_02261ce4 @ 0x02261ce4, 0x24 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(void *a, void *b, void *c);
extern void *data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} SelfType;

void func_ov048_02261ce4(SelfType *self, int flag)
{
    if (flag == 0) {
        char local = 25;
        func_0206844c(self->unk_40, &local, data_ov048_02263d20);
    }
}
