/* func_ov068_0226e7ac @ 0x0226e7ac, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0226e7ac *func_02095794(int);
extern int func_02095ab0(void *, unsigned int, unsigned int);

struct UnkStruct_0226e7ac {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

int func_ov068_0226e7ac(void)
{
    struct UnkStruct_0226e7ac *src;
    struct UnkStruct_0226e7ac local;

    src = func_02095794(4);
    local.a = src->a;
    local.b = src->b;
    local.c = src->c;
    local.c += 0x2000;
    func_02095ab0(&local, 0x400, 4);
    return 1;
}
