/* func_ov003_0222e264 @ 0x0222e264, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov003_0223c146[];

int func_ov003_0222e264(int a, unsigned char *o)
{
    signed char v = (signed char) o[0x24d];

    if (*(unsigned short *) ((char *) data_ov003_0223c146 + v * 6) <= 1) {
        return 0;
    }

    switch (v) {
        case 0x1e:
        case 0x31:
            if (o[0x251] != 0x13) {
                return 1;
            }
            return 0;
        case 0x18:
        case 0x30:
        case 0x32:
        case 0x33:
        case 0x3a:
        case 0x3b:
            return 0;
        default:
            return 1;
    }
}
