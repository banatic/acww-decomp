/* func_0206a67c @ 0x0206a67c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206a854(void *);
extern void *func_0206837c(void *);
extern void func_020ab4a8(void *);

typedef struct {
    char pad_00[0x24];
    void *unk_24;
} UnkStruct_0206a67c;

void func_0206a67c(UnkStruct_0206a67c *arg)
{
    func_0206a854(arg);
    func_020ab4a8(func_0206837c(arg->unk_24));
}
