/* func_0205d0d4 @ 0x0205d0d4, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x[0x14];
} UnkStruct_0205d0d4;
typedef struct {
    unsigned char pad_00[0x10];
    UnkStruct_0205d0d4 arr[4];
} UnkStruct_0205d0d4_2;
void *func_0205d0d4(UnkStruct_0205d0d4_2 *p, int i)
{
    return &p->arr[i];
}
