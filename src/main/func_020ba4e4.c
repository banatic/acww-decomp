/* func_020ba4e4 @ 0x020ba4e4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x0c];
    int unk_34;
} Unk021F8AB0;

extern Unk021F8AB0 data_021f8ab0;

int func_020ba4e4(void)
{
    switch (data_021f8ab0.unk_24) {
        case 2:
        case 3:
        case 4:
            switch (data_021f8ab0.unk_34) {
                case 1:
                    return 1;
                case 2:
                    return 2;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}
