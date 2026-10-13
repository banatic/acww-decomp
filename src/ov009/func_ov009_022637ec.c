/* func_ov009_022637ec @ 0x022637ec, 0x9c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O1,s
 */

extern int func_020b2470(unsigned short);
extern int func_ov009_02264c90(void *);
extern void func_ov009_022639a0(void *, int);

typedef union {
    unsigned char byte_236;
    struct {
        unsigned char : 1;
        unsigned char bit236_1 : 1;
        unsigned char : 6;
    } bits;
} B236;

typedef struct {
    unsigned char pad_00[0x136];
    unsigned short unk_136;
    unsigned char pad_138[0x236 - 0x138];
    B236 unk_236;
    unsigned char unk_237;
    unsigned char pad_238[0x280 - 0x238];
    unsigned char unk_280;
} UnkStruct_022637ec;

void func_ov009_022637ec(UnkStruct_022637ec *self)
{
    if (!self->unk_280) {
        int ret = func_020b2470(self->unk_136);
        if (ret != 0) {
            unsigned int flag = (ret == 2);
            self->unk_236.byte_236 = (self->unk_236.byte_236 & ~2) | ((flag & 1) << 1);
            self->unk_237 = (ret == 3);
            if (self->unk_236.bits.bit236_1 || self->unk_237) {
                func_ov009_022639a0(self, 2);
            } else {
                int r = func_ov009_02264c90(self);
                if (r == 1) {
                    func_ov009_022639a0(self, 7);
                } else {
                    func_ov009_022639a0(self, 4);
                }
            }
        }
    } else {
        func_ov009_022639a0(self, 2);
    }
}
