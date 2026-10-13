/* func_02032694 @ 0x02032694, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02032694 UnkStruct_02032694;
struct UnkStruct_02032694 {
    char pad_00[0x38];
    UnkStruct_02032694 *unk_38;
};
extern UnkStruct_02032694 *data_021c30e0;

int func_02032694(UnkStruct_02032694 *p)
{
    if (p->unk_38 == 0) {
        p->unk_38 = data_021c30e0;
        data_021c30e0 = p;
        return 1;
    } else {
        return 0;
    }
}
