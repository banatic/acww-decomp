/* func_ov134_0229af60 @ 0x0229af60, 0x14 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229af74(void *self, unsigned char a, unsigned char b);

typedef struct {
    char pad_00[0xb9];
    unsigned char b9;
    unsigned char ba;
} UnkStruct_0229af60;

int func_ov134_0229af60(UnkStruct_0229af60 *self)
{
    return func_ov134_0229af74(self, self->ba, self->b9);
}
