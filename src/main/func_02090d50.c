/* func_02090d50 @ 0x02090d50, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int pad_00[3];
    unsigned int unk_0C;
} UnkStruct_02090d50;

extern void func_02090db0(unsigned int);

int func_02090d50(UnkStruct_02090d50 *p)
{
    func_02090db0(p->unk_0C);
    return 1;
}
