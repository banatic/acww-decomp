/* func_ov147_02299408 @ 0x02299408, 0xc bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov147_02299fc8(void *arg1, int arg2);
typedef struct {
    char pad_00[0x48];
    void *unk_48;
} some_struct;
int func_ov147_02299408(some_struct *self)
{
    return func_ov147_02299fc8(self->unk_48, 6);
}
