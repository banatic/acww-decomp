/* func_02089c50 @ 0x02089c50, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char sub;
} UnkStruct_02089c50;
typedef struct {
    unsigned char pad_00[0x40];
    UnkStruct_02089c50 *ptr;
} UnkStruct_02089c50_2;
void *func_02089c50(UnkStruct_02089c50_2 *p)
{
    return &p->ptr->sub;
}
