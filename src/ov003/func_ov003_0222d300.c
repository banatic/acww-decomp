/* func_ov003_0222d300 @ 0x0222d300, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_ov003_02260554;
extern char data_ov003_022617bc[];

void func_ov003_0222d300(void)
{
    data_ov003_02260554++;
    if (data_ov003_02260554 > 0x78) {
        char *o = data_ov003_022617bc;
        int i;
        data_ov003_02260554 = 0;
        for (i = 0; i < 8; i++) {
            if (*(signed char *) (o + 0x24d) == -10) {
                *(char *) (o + 0x24d) = -1;
                *(char *) (o + 0x248) = 0;
            } else if (*(unsigned char *) (o + 0x249) == 0 && *(short *) (o + 0x234) == 0 &&
                       *(unsigned char *) (o + 0x250) == 3) {
                *(char *) (o + 0x250) = 4;
                *(char *) (o + 0x251) = 0xa;
            }
            o += 0x25c;
        }
    }
}
