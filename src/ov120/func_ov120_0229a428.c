/* func_ov120_0229a428 @ 0x0229a428, 0xe bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    unsigned short flags;
} UnkStruct_0229a428;

void func_ov120_0229a428(UnkStruct_0229a428 *self, unsigned short mask)
{
    self->flags &= ~mask;
}
