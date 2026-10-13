/* func_02087854 @ 0x02087854, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} SrcStruct;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} DstStruct;

int func_02087854(SrcStruct *src, DstStruct *dst)
{
    dst->unk_00 = src->unk_00;
    dst->unk_08 = src->unk_04;
    dst->unk_04 = 0;
    return 0;
}
