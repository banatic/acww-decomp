/* func_ov068_02275358 @ 0x02275358, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct InnerOverlay {
    int unk_00;
    int unk_04;
};

struct OuterOverlay {
    char pad_00[0x8DC];
    struct InnerOverlay *ptr;
};

void func_0203e020(struct OuterOverlay *self, int arg);

void func_ov068_02275358(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020(self, self->ptr->unk_04);
    }
}
