/* func_020b4b48 @ 0x020b4b48, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4b48 {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x10];
    int unk_38;
    int unk_3C;
};

extern void func_020b4afc(struct UnkStruct_020b4b48 *self, int arg);

void func_020b4b48(struct UnkStruct_020b4b48 *self, int arg)
{
    int state;
    self->unk_38 = arg;
    state = self->unk_24;
    if (state == 1) {
        func_020b4afc(self, arg);
        if (arg != 10) {
            self->unk_3C--;
        }
    } else if (state == 2) {
        if (arg == 10) {
            func_020b4afc(self, 10);
        } else {
            func_020b4afc(self, 0x3000);
            self->unk_3C--;
        }
    } else if (state == 3) {
        if (arg != 10) {
            self->unk_3C--;
        }
    }
}
