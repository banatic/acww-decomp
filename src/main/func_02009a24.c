/* func_02009a24 @ 0x02009a24, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_02009a24;

void func_02009a24(int *dst, UnkStruct_02009a24 s, int p4, int p5)
{
    dst[0] = s.a;
    dst[1] = s.b;
    dst[2] = s.c;
    dst[3] = 0;
    dst[4] = p4;
    dst[5] = p5;
}
