/* func_02062870 @ 0x02062870, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern unsigned char *func_0206e7bc(void *, unsigned int);

extern unsigned char data_021cb5e0[];

unsigned char func_02062870(unsigned short *param)
{
    unsigned int mask_val;
    unsigned char *result;

    mask_val = *param & 0xfff;
    if (mask_val >= 0x56e) {
        mask_val = 0x56d;
    }

    result = func_0206e7bc(func_0206e6ec((void *) data_021cb5e0), mask_val);
    if (result != 0) {
        return result[4];
    } else {
        return 0;
    }
}
