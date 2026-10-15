/* func_0201a6c8 @ 0x0201a6c8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201a720(void *obj, void *field, int count);
extern void func_0201a714(void *obj, void *field, unsigned int a, unsigned int b);

struct UnkStruct_0201a6c8 {
    char pad_00[0x10];
    char unk_10[0xC];
    unsigned int unk_1C;
};

void func_0201a6c8(struct UnkStruct_0201a6c8 *s, unsigned int a, unsigned int b, unsigned int c)
{
    func_0201a720(s, s->unk_10, 2);
    func_0201a714(s, s->unk_10, a, b);
    s->unk_1C = c;
}
