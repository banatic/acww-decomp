/* func_ov003_02218108 @ 0x02218108, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern void func_0200f888(void *self);

typedef struct {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d5 - 0x708];
    unsigned char unk_7D5;
} UnkStruct_02218108;

void func_ov003_02218108(UnkStruct_02218108 *self)
{
    unsigned char *p = &self->unk_7D5;
    int v;
    unsigned char c;

    func_02010f5c(self);
    c = self->unk_7D5;
    if (c != 0) {
        *p = (unsigned char) (c - 1);
        if (*p == 0) {
            if (self->unk_704 == 0x36) {
                func_020109a0(self, 0x35, 5, 0);
            }
        }
    } else {
        if (self->unk_704 == 0x34) {
            v = (int) ((self->unk_2D8 << 4) >> 16);
            switch (v) {
                case 0xd:
                case 0x11:
                case 0x17:
                case 0x1c:
                case 0x25:
                case 0x28:
                    func_0200f888(self);
                    break;
            }
        } else if (self->unk_704 == 0x35) {
            v = (int) ((self->unk_2D8 << 4) >> 16);
            switch (v) {
                case 4:
                case 9:
                case 0xe:
                case 0x14:
                    func_0200f888(self);
                    break;
            }
        }
    }
}
