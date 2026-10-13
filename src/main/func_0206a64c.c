/* func_0206a64c @ 0x0206a64c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206a64c {
    char pad_00[0x24];
    void *unk_24;
} UnkStruct_0206a64c;

extern void func_0206a6ac(UnkStruct_0206a64c *s);
extern void *func_0206837c(void *s);
extern void func_020ab4a8(void *s);

void func_0206a64c(UnkStruct_0206a64c *s)
{
    func_0206a6ac(s);
    func_020ab4a8(func_0206837c(s->unk_24));
}
