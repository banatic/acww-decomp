/* func_020b6468 @ 0x020b6468, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b6468 {
    unsigned char b;
    char pad_01;
    short s1;
    int i1;
    int i2;
    int i3;
    int v;
    unsigned char c1;
    unsigned char c2;
    short s2;
    unsigned char c3;
};

void func_020b6468(struct UnkStruct_020b6468 *out, unsigned char b, int *data, int v, short s1, unsigned char c1,
                   unsigned char c2, short s2, unsigned char c3)
{
    out->b = b;
    out->i1 = data[0];
    out->i2 = data[1];
    out->i3 = data[2];
    out->v = v;
    out->s1 = s1;
    out->c1 = c1;
    out->c2 = c2;
    out->s2 = s2;
    out->c3 = c3;
}
