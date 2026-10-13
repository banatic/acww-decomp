/* func_020f0ccc @ 0x020f0ccc, 0x70 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct KbdWork {
    unsigned char pad_00[0x44];
    int mode;
} KbdWork;
int func_020f0ccc(KbdWork *self, unsigned short idx)
{
    switch (idx) {
        case 0:
            idx = 0;
            break;
        default:
            switch (self->mode) {
                case 0:
                case 4:
                    idx = idx + 0xce;
                    break;
                case 1:
                case 3:
                    idx = idx + 0x140;
                    break;
                case 2:
                    idx = idx + 0x1b2;
                    break;
            }
            break;
    }
    return idx;
}
