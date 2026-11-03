/* villager_talk_scene_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202dbf0 @ 0x0202dbf0, 0x14 bytes, Thumb
 * func_0202dbdc @ 0x0202dbdc, 0x14 bytes, Thumb
 */

typedef struct Pair {
    int x;
    int y;
} Pair;

typedef struct {
    int a;
    int b;
} UnkStruct_0202dbdc;

typedef struct {
    unsigned char pad_00[0xe0];
    UnkStruct_0202dbdc v;
} UnkStruct_0202dbdc_2;

void func_0202dbf0(int *p, Pair value)
{
    int a;
    int b;
    a = *(volatile int *) &value.x;
    b = *(volatile int *) &value.y;
    p[0x36] = a;
    p[0x37] = b;
}

void func_0202dbdc(UnkStruct_0202dbdc_2 *p, UnkStruct_0202dbdc v)
{
    p->v = v;
}
