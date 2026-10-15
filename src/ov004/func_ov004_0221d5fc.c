/* func_ov004_0221d5fc @ 0x0221d5fc, 0x20 bytes, Thumb, module ov004
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

int func_0203e020(struct OuterOverlay *self);

void func_ov004_0221d5fc(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020(self);
    }
}
