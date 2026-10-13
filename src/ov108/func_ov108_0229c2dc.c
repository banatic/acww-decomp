/* func_ov108_0229c2dc @ 0x0229c2dc, 0x12 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct Unknown_0229c2dc {
    char pad_00[0x94];
    unsigned int unk_94;
};

int func_ov108_0229c2dc(struct Unknown_0229c2dc *p, unsigned int mask)
{
    if ((p->unk_94 & mask) != 0) {
        return 1;
    }
    return 0;
}
