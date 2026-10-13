/* func_020f5c64 @ 0x020f5c64, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    int unk_00;
} UnkStruct_020f5c64;

int func_020f5c64(UnkStruct_020f5c64 *self, int mode)
{
    int raw, result;
    if (self == 0) {
        return 0;
    }
    raw = self->unk_00 >> 12;
    switch (mode) {
        case 0:
            result = (raw + 0x2a) * 0xdd / 83 - 0x6f;
            break;
        case 1:
            if (raw > 0) {
                result = 1;
            } else {
                if (raw < 0) {
                    result = 1;
                } else {
                    result = 0;
                }
                result = -result;
            }
            break;
        case 2:
            result = raw - 0x80;
            break;
        default:
            result = (int) self;
            break;
    }
    if (result < -128) {
        return -128;
    }
    if (result > 127) {
        result = 127;
    }
    return result;
}
