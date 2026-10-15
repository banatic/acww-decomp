/* func_ov066_0226b594 @ 0x0226b594, 0x30 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short func_ov066_0226b5c4(void *p);
extern void func_ov066_0226b7ac(void);

struct UnkStruct_0226b594 {
    char pad_00[0x24];
    union {
        unsigned char byte;
        struct {
            unsigned char b0 : 1;
            unsigned char b1 : 1;
            unsigned char b2 : 1;
        } bits;
    } u;
};

void func_ov066_0226b594(struct UnkStruct_0226b594 *self)
{
    func_ov066_0226b5c4(&self->u.byte);
    if (!self->u.bits.b2) {
        return;
    }
    func_ov066_0226b7ac();
}
