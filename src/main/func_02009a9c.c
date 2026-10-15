/* func_02009a9c @ 0x02009a9c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
    int d;
} UnkStruct_02009a9c;
typedef struct Triple_02009a9c {
    int a;
    int b;
    int c;
} Triple_02009a9c;

void func_02009a9c(UnkStruct_02009a9c *out, Triple_02009a9c v, int arg)
{
    out->a = v.a;
    out->b = v.b;
    out->c = v.c;
    out->d = arg;
}
