/* func_0205d0c8 @ 0x0205d0c8, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char x[0x1c];
} UnkStruct_0205d0c8;
typedef struct {
    unsigned char pad_00[0x60];
    UnkStruct_0205d0c8 arr[4];
} UnkStruct_0205d0c8_2;
void *func_0205d0c8(UnkStruct_0205d0c8_2 *p, int i)
{
    return &p->arr[i];
}
