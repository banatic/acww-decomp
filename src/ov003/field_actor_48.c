/* field_actor_48: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022178b0 @ 0x022178b0, 0x1a bytes, Thumb
 * func_ov003_02217894 @ 0x02217894, 0x1c bytes, Thumb
 */

struct UnkStruct_02217894 {
    int a;
    int b;
    int c;
    short d;
    char e;
};

extern void func_02010f5c(int);
extern void func_02010d64(int);
extern void func_ov003_022178cc(int);

void func_ov003_022178b0(int x)
{
    func_02010f5c(x);
    func_02010d64(x);
    func_ov003_022178cc(x);
}

void func_ov003_02217894(struct UnkStruct_02217894 *out, int a, char b, int c, int d, short e)
{
    out->a = a;
    out->e = b;
    out->b = c;
    out->c = d;
    out->d = e;
}
