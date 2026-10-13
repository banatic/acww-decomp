/* func_02050948 @ 0x02050948, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    int unk_04;
} UnkStruct_02050948;

extern void func_0211ec34(unsigned short);
extern void OS_ReleaseLockID(unsigned short);

void func_02050948(UnkStruct_02050948 *p)
{
    if (p->unk_04 == ~2) {
        return;
    }
    func_0211ec34((unsigned short) p->unk_04);
    OS_ReleaseLockID((unsigned short) p->unk_04);
    p->unk_04 = ~2;
}
