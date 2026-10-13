/* func_ov105_0229d1f0 @ 0x0229d1f0, 0x40 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d1f0 {
    char pad_00[0xac];
    unsigned int unk_AC;
    unsigned int unk_B0;
    char pad_B4[0x200];
    unsigned char unk_2B4;
};

extern int func_ov105_0229c340(void *p, int n);
extern void func_ov094_0229b5e8(void *a, unsigned int b, unsigned int c, void *d);

void func_ov105_0229d1f0(struct UnkStruct_0229d1f0 *p)
{
    if (func_ov105_0229c340(p, 0x40) != 0) {
        return;
    }
    if (p->unk_2B4 == 0) {
        return;
    }
    if (p->unk_2B4 != 1) {
        return;
    }
    func_ov094_0229b5e8((void *) ((char *) p + 0xd5c), p->unk_AC, p->unk_B0, (void *) ((char *) p + 0xb4));
}
