/* func_0201ad78 @ 0x0201ad78, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Src;

typedef struct {
    unsigned char pad_00[8];
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Dst;

void func_0201ad78(Dst *dst, const Src *src)
{
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
}
