/* func_ov003_0222d7d0 @ 0x0222d7d0, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_022617bc[];
extern char data_ov003_02260994[];

int func_ov003_0222d7d0(int code)
{
    unsigned char i = (unsigned char) (code & 0xf);
    char *o = (char *) code;
    if ((code >> 4) & 1) {
        o = data_ov003_022617bc + 0x25c * i;
    } else if ((code >> 5) & 1) {
        o = data_ov003_02260994 + 0x25c * i;
    }
    if (*(unsigned char *) (o + 0x251) != 0xa && *(unsigned char *) (o + 0x251) != 0xb &&
        *(unsigned char *) (o + 0x251) != 9 && *(unsigned char *) (o + 0x251) != 0x10 && *(unsigned char *) (o + 0x250) == 3) {
        *(char *) (o + 0x251) = 0x10;
        return 0;
    }
    return 1;
}
