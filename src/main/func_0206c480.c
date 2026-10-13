/* func_0206c480 @ 0x0206c480, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206c480 {
    unsigned int pad_00[11];
    unsigned int unk_2C;
} UnkStruct_0206c480;

extern int func_0206d420(UnkStruct_0206c480 *self, unsigned int a, unsigned int b);

int func_0206c480(UnkStruct_0206c480 *self)
{
    unsigned int base;
    unsigned int tmp;

    base = self->unk_2C;
    tmp = base + 0x18ac;
    return func_0206d420(self, tmp + 0x114, tmp);
}
