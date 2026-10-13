/* func_0206947c @ 0x0206947c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
} UnkStruct_0206947c;

extern int func_0206b97c(UnkStruct_0206947c *self, unsigned int a, unsigned int b);

int func_0206947c(UnkStruct_0206947c *self)
{
    unsigned int inter = self->unk_24 + 0x14b8;
    return func_0206b97c(self, inter + 0x170, inter);
}
