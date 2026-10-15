/* func_020aae78 @ 0x020aae78, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ab504(void *arg1);

typedef struct {
    char pad_00[0x34];
    void *unk_34;
} UnkStruct_020aae78;

int func_020aae78(UnkStruct_020aae78 *self)
{
    return func_020ab504(self->unk_34);
}
