/* func_ov002_0220a530 @ 0x0220a530, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aef0(void *p);
struct UnkStruct_0220a530 {
    char pad_00[0xc];
    int unk_0C;
};
int func_ov002_0220a530(struct UnkStruct_0220a530 *p)
{
    int r = func_0208aef0(p);
    return p->unk_0C + r;
}
