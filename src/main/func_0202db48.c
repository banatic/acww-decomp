/* func_0202db48 @ 0x0202db48, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_0202db48;
typedef struct {
    unsigned char pad_00[0xe8];
    UnkStruct_0202db48 v;
} UnkStruct_0202db48_2;
void func_0202db48(UnkStruct_0202db48_2 *p, UnkStruct_0202db48 v)
{
    p->v = v;
}
