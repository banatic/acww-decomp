/* func_0205df40 @ 0x0205df40, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x[0x14];
} UnkStruct_0205df40;
typedef struct {
    unsigned char pad_00[0x10];
    UnkStruct_0205df40 arr[4];
} UnkStruct_0205df40_2;
void *func_0205df40(UnkStruct_0205df40_2 *p, int i)
{
    return &p->arr[i];
}
