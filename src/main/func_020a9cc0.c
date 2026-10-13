/* func_020a9cc0 @ 0x020a9cc0, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x18];
    int unk_18;
} UnkStruct_020a9cc0;
int *func_020a9cc0(UnkStruct_020a9cc0 *p)
{
    return (int *) p + (p->unk_18 - 1);
}
