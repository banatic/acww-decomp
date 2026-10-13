/* func_02055c18 @ 0x02055c18, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
} UnkStruct_02055c18;

extern int func_02055bd8(UnkStruct_02055c18 *, int, int, int);

int func_02055c18(UnkStruct_02055c18 *a, int b, int c)
{
    return func_02055bd8(a, c, a->unk_08, b);
}
