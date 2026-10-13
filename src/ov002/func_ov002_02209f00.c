/* func_ov002_02209f00 @ 0x02209f00, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aef0(void *p);
struct UnkStruct_02209f00 {
    char pad_00[0x20];
    int unk_20;
};
int func_ov002_02209f00(struct UnkStruct_02209f00 *p)
{
    int r = func_0208aef0(p);
    return p->unk_20 + r;
}
