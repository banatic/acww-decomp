/* func_02053450 @ 0x02053450, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02053450 {
    unsigned char flag;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned char val;
};

struct In {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

int func_02053450(struct UnkStruct_02053450 *out, unsigned char val, struct In *in)
{
    out->flag = 1;
    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    out->val = val;
    return 1;
}
