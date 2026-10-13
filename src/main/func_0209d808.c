/* func_0209d808 @ 0x0209d808, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Src;
typedef struct {
    int pad_00[4];
    int a, b, c;
} Dest;

void func_0209d808(Dest *dest, const Src *src)
{
    dest->a = src->a;
    dest->b = src->b;
    dest->c = src->c;
}
