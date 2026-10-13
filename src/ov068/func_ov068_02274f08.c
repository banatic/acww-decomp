/* func_ov068_02274f08 @ 0x02274f08, 0x10 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x294];
    int flag;
} UnkStruct_02274f08;

int func_ov068_02274f08(UnkStruct_02274f08 *self)
{
    self->flag = 1;
    return 1;
}
