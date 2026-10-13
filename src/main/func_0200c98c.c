/* func_0200c98c @ 0x0200c98c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0200c98c {
    char pad_00[0xC];
    unsigned short unk_0C;
};

extern int func_020109fc(void *arg0, int arg1, unsigned short arg2, unsigned short arg3);
extern int func_0200eebc(void *arg0);

int func_0200c98c(void *arg0, struct UnkStruct_0200c98c *arg1)
{
    unsigned short x = arg1->unk_0C;
    func_020109fc(arg0, 18, x, x);
    return func_0200eebc(arg0);
}
