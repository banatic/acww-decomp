/* func_02060438 @ 0x02060438, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Src;
typedef struct {
    char pad_00[0x1c];
    int a, b, c;
} Dst;

void func_02060438(Dst *d, Src *s)
{
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
}
