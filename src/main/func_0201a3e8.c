/* func_0201a3e8 @ 0x0201a3e8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x84];
    unsigned char flag;
} UnkStruct_0201a3e8;

int func_0201a3e8(UnkStruct_0201a3e8 *self)
{
    if (self->flag != 0) {
        return 1;
    } else {
        return 0;
    }
}
