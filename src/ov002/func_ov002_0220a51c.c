/* func_ov002_0220a51c @ 0x0220a51c, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aeec(void *p);
struct UnkStruct_0220a51c {
    char pad_00[0x10];
    int unk_10;
};
int func_ov002_0220a51c(struct UnkStruct_0220a51c *p)
{
    int r = func_0208aeec(p);
    return p->unk_10 + r;
}
