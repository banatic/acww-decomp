/* func_020549fc @ 0x020549fc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14c];
    unsigned int low;
    unsigned int high;
} Flags;

int func_020549fc(Flags *flags, unsigned int index)
{
    if (index >= 32) {
        if (flags->high & (1 << (index - 32))) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (flags->low & (1 << index)) {
            return 1;
        } else {
            return 0;
        }
    }
}
