/* func_ov105_0229c354 @ 0x0229c354, 0x58 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0229c354 {
    unsigned short pad_00;
    unsigned short flags;
} data_021fbe40;

extern void func_ov105_0229c3ec(void *arg0);

int func_ov105_0229c354(unsigned char *self)
{
    int x = 0;
    unsigned short f = data_021fbe40.flags;

    if (f & 0x200) {
        x = -1;
    } else if (f & 0x100) {
        x = 1;
    }

    if (x != 0) {
        x += self[0x2c0];
        if (x < 0) {
            x = 1;
        } else if (x > 1) {
            x = 0;
        }
        self[0x2c0] = (unsigned char) x;
        func_ov105_0229c3ec((void *) self);
    }

    return 0;
}
