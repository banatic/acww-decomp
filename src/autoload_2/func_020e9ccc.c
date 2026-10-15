/* func_020e9ccc @ 0x020e9ccc, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern int func_02101c54(int, void *block, unsigned int size);

typedef struct {
    char pad_00[0x14];
    int unk_14;
} UnkStruct_020e9ccc;

int func_020e9ccc(UnkStruct_020e9ccc *self, void *block, unsigned int size)
{
    return func_02101c54(self->unk_14, block, size);
}
