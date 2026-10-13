/* func_ov003_02217894 @ 0x02217894, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02217894 {
    int a;
    int b;
    int c;
    short d;
    char e;
};

void func_ov003_02217894(struct UnkStruct_02217894 *out, int a, char b, int c, int d, short e)
{
    out->a = a;
    out->e = b;
    out->b = c;
    out->c = d;
    out->d = e;
}
