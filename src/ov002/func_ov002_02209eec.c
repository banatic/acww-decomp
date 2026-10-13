/* func_ov002_02209eec @ 0x02209eec, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aeec(void *p);
struct UnkStruct_02209eec {
    char pad_00[0x24];
    int unk_24;
};
int func_ov002_02209eec(struct UnkStruct_02209eec *p)
{
    int r = func_0208aeec(p);
    return p->unk_24 + r;
}
