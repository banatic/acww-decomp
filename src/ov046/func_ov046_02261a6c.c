/* func_ov046_02261a6c @ 0x02261a6c, 0x34 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *arg0);
extern void func_0209129c(int);

typedef struct {
    char pad_00[0x740];
    int unk_740;
} UnkStruct_02261a6c;

int func_ov046_02261a6c(UnkStruct_02261a6c *self)
{
    if (func_0202ec14((void *) self) == 0) {
        return 0;
    }
    if (self->unk_740 != -1) {
        func_0209129c(self->unk_740);
        self->unk_740 = -1;
    }
    return 1;
}
