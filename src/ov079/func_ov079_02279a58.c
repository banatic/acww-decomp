/* func_ov079_02279a58 @ 0x02279a58, 0x3a bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(int *out, void *in, int c, short s);
extern int func_0201ae8c(int *buf);

struct Src {
    char pad_00[0x5c];
    char sub;
    char pad_5D[0x37];
    short unk_94;
};

struct Dst {
    int x, y, z;
};

int func_ov079_02279a58(struct Src *src, struct Dst *dst, int c)
{
    int buffer[4];
    int result = 0;
    func_0201af58(buffer, &src->sub, c, src->unk_94);
    if (func_0201ae8c(buffer) != 1) {
        dst->x = buffer[0];
        dst->y = buffer[1];
        dst->z = buffer[2];
        result = 1;
    }
    return result;
}
