/* func_02089c48 @ 0x02089c48, 0x6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[4];
    void *unk_04;
} UnkStruct_02089c48;
typedef struct {
    unsigned char pad_00[0x40];
    UnkStruct_02089c48 *ptr;
} UnkStruct_02089c48_2;
void *func_02089c48(UnkStruct_02089c48_2 *p)
{
    return p->ptr->unk_04;
}
