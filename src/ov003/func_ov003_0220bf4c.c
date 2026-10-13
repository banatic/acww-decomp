/* func_ov003_0220bf4c @ 0x0220bf4c, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkInner {
    int unk_00;
    void *unk_04;
};

struct UnkOuter {
    char pad_00[0x12c];
    struct UnkInner *unk_12C;
};

extern void func_ov003_0220c064(void *obj, int mode);

void func_ov003_0220bf4c(struct UnkOuter *obj)
{
    if (obj->unk_12C != 0 && obj->unk_12C->unk_04 != 0) {
        func_ov003_0220c064(obj, 2);
    }
}
