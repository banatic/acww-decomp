/* func_020606f0 @ 0x020606f0, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x[0x14];
} UnkStruct_020606f0;
typedef struct {
    unsigned char pad_00[0x24];
    UnkStruct_020606f0 arr[4];
} UnkStruct_020606f0_2;
void *func_020606f0(UnkStruct_020606f0_2 *p, int i)
{
    return &p->arr[i];
}
