/* func_ov051_0226079c @ 0x0226079c, 0x8c bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int argument0);
extern void func_020950c8(int, int);
extern int func_020a12c0(void);
extern void func_0206844c(unsigned int, unsigned char *, int);
extern int data_ov051_022615c0;

struct UnkStruct_0226079c {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
};

extern unsigned char func_ov051_022605e8(struct UnkStruct_0226079c *, int);

void func_ov051_0226079c(struct UnkStruct_0226079c *self, int which)
{
    unsigned char buf[3];

    switch (which) {
        case 0:

            func_020950c8(func_02099870((int) func_020984e8()), 1);
            if (func_020a12c0()) {
                buf[0] = func_ov051_022605e8(self, 0x19);
                func_0206844c(self->unk_40, buf, data_ov051_022615c0);
            } else {
                buf[1] = func_ov051_022605e8(self, 0xf);
                func_0206844c(self->unk_40, &buf[1], data_ov051_022615c0);
            }
            break;
        case 1:

            func_020950c8(func_02099870((int) func_020984e8()), 0);
            buf[2] = 0xd;
            func_0206844c(self->unk_40, &buf[2], data_ov051_022615c0);
            break;
        default:
            break;
    }
}
