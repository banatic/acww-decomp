/* func_02090f88 @ 0x02090f88, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02090f88;
typedef struct UnkStruct_02090f88_2 UnkStruct_02090f88_2;
extern int func_0203f8d0(UnkStruct_02090f88_2 *p, UnkStruct_02090f88 *t);
unsigned short func_02090f88(UnkStruct_02090f88_2 *p, UnkStruct_02090f88 v)
{
    UnkStruct_02090f88 t;
    t.a = v.a;
    t.b = v.b;
    t.c = v.c;
    return (unsigned short) func_0203f8d0(p, &t);
}
