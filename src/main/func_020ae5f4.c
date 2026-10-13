/* func_020ae5f4 @ 0x020ae5f4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    signed char v;
} UnkStruct_020ae5f4;

int func_020ae5f4(volatile UnkStruct_020ae5f4 *self)
{
    if (self->v == -1) {
        return 0;
    }
    return (unsigned char) (self->v * 2 + 1);
}
