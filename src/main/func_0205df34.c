/* func_0205df34 @ 0x0205df34, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x[0x1c];
} UnkStruct_0205df34;
typedef struct {
    unsigned char pad_00[0x60];
    UnkStruct_0205df34 arr[4];
} UnkStruct_0205df34_2;
void *func_0205df34(UnkStruct_0205df34_2 *p, int i)
{
    return &p->arr[i];
}
