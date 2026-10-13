/* func_02061204 @ 0x02061204, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x448];
    unsigned char pad_448[6];
    unsigned char flag : 1;
} UnkStruct_02061204;

UnkStruct_02061204 *func_02061204(UnkStruct_02061204 *self, int *out)
{
    if (out) {
        *out = self->flag;
    }
    return (UnkStruct_02061204 *) ((char *) self + 0x448);
}
