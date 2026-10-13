/* func_ov003_022186b0 @ 0x022186b0, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022186b0 {
    int a;
    int b;
    short c;
    char d;
    char e;
};

void func_ov003_022186b0(struct UnkStruct_022186b0 *out, char a, int b, int c, short d, unsigned char e)
{
    out->d = a;
    out->a = b;
    out->b = c;
    out->c = d;
    out->e = e;
}
