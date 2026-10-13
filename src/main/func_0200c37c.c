/* func_0200c37c @ 0x0200c37c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *param0, int param1);
extern void func_020109fc(void *param0, int param1, unsigned short param2, int param3);
extern void func_0200eebc(void *param0);
extern void func_0200f268(void *param0, int param1);

struct Struct0200c37c {
    char pad_00[0xC];
    unsigned short unk_0C;
};

void func_0200c37c(void *arg0, struct Struct0200c37c *arg1)
{
    unsigned short field;
    field = arg1->unk_0C;
    if (func_0200f290(arg0, 23) == 0) {
        func_020109fc(arg0, 0, field, 0);
    }
    func_0200eebc(arg0);
    func_0200f268(arg0, 29);
}
