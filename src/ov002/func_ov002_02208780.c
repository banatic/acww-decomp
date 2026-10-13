/* func_ov002_02208780 @ 0x02208780, 0x1a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x0c];
    int value;
    char pad_10[0x08];
    unsigned char flag;
} UnkStruct_02208780;

int func_ov002_02208780(UnkStruct_02208780 *self)
{
    switch (self->flag) {
        case 0:
            return self->value;
        case 1:
            return -self->value;
        default:
            return 0;
    }
}
