/* func_0206a664 @ 0x0206a664, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206a664 {
    char pad_00[0x24];
    unsigned int unk_24;
};

extern void func_0206a790(struct UnkStruct_0206a664 *);
extern unsigned int func_0206837c(unsigned int);
extern void func_020ab4a8(void *object);

void func_0206a664(struct UnkStruct_0206a664 *arg0)
{
    func_0206a790(arg0);
    func_020ab4a8((void *) func_0206837c(arg0->unk_24));
}
