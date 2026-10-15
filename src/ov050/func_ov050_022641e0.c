/* func_ov050_022641e0 @ 0x022641e0, 0x30 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019c6c(void *, int, unsigned short);

int func_ov050_022641e0(void *param)
{
    unsigned short *p = (unsigned short *) ((char *) param + 0x730);
    *p = data_020c80f8;
    func_02019c6c((char *) param + 0x564, 1, *p);
    return 1;
}
