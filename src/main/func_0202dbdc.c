/* func_0202dbdc @ 0x0202dbdc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_0202dbdc;
typedef struct {
    unsigned char pad_00[0xe0];
    UnkStruct_0202dbdc v;
} UnkStruct_0202dbdc_2;
void func_0202dbdc(UnkStruct_0202dbdc_2 *p, UnkStruct_0202dbdc v)
{
    p->v = v;
}
