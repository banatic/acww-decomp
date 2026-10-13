/* func_02054d80 @ 0x02054d80, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb8];
    char sub[0x38];
    int unk_F0;
} UnkStruct_02054d80;

extern void func_02056aa0(void *sub, int arg);

void func_02054d80(UnkStruct_02054d80 *self, int arg)
{
    if (self->unk_F0 != 0) {
        func_02056aa0(self->sub, arg);
    }
}
