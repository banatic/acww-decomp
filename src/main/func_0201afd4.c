/* func_0201afd4 @ 0x0201afd4, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Vec3;

typedef struct {
    unsigned char pad_00[0x44];
    Vec3 v;
} UnkStruct_0201afd4;

void func_0201afd4(UnkStruct_0201afd4 *dst, const Vec3 *src)
{
    dst->v.a = src->a;
    dst->v.b = src->b;
    dst->v.c = src->c;
}
