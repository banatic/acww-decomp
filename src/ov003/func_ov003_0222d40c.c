/* func_ov003_0222d40c @ 0x0222d40c, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222d40c;
extern UnkStruct_0222d40c *data_020ccf94;
extern int func_02073dd4(UnkStruct_0222d40c *g, int a);

int func_ov003_0222d40c(int k)
{
    if (!func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
        return 1;
    }

    switch (k) {
        case 8:
        case 0xa:
        case 0x19:
        case 0x23:
        case 0x30:
        case 0x32:
        case 0x33:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x3a:
        case 0x3b:
            return 0;
        default:
            return 1;
    }
}
