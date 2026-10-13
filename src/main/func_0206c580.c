/* func_0206c580 @ 0x0206c580, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void *a, void *b, void *c);

struct Func0206c580_Unk {
    char pad_00[0x2c];
    char *ptr;
};

void func_0206c580(struct Func0206c580_Unk *self)
{
    char *start;
    start = self->ptr + 0x14b8;
    func_0206d420(self, start + 0x170, start);
}
