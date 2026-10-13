/* func_020f5e14 @ 0x020f5e14, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f5e24(int arg);

typedef struct {
    char pad_00[0x10];
    int unk_10;
} UnkStruct_020f5e14;

int func_020f5e14(UnkStruct_020f5e14 *self)
{
    return func_020f5e24(self->unk_10);
}
