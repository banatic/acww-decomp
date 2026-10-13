/* func_020606e4 @ 0x020606e4, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x[0x1c];
} UnkStruct_020606e4;
typedef struct {
    unsigned char pad_00[0xd8];
    UnkStruct_020606e4 arr[4];
} UnkStruct_020606e4_2;
void *func_020606e4(UnkStruct_020606e4_2 *p, int i)
{
    return &p->arr[i];
}
