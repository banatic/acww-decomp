/* func_020579b8 @ 0x020579b8, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    unsigned short unk_34;
} UnkStruct_020579b8;

extern int func_02057a98(void *p, const char *name);

int func_020579b8(UnkStruct_020579b8 *self, const char *name)
{
    return func_02057a98((char *) self + self->unk_34, name);
}
