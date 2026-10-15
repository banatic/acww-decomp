/* func_ov095_0229b324 @ 0x0229b324, 0x64 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_02002c6c(void *, void *, int, int, int, int);
extern void *data_021fbe94;

extern unsigned char data_ov095_0229ee08[];
extern unsigned char data_ov095_0229ee24[];
extern unsigned char data_ov095_0229ee40[];

int func_ov095_0229b324(void)
{
    void *obj = data_021fbe94;

    func_02002d14((void *) data_ov095_0229ee08, obj, 8, 4, 4, 0xe);
    func_02002c6c((void *) data_ov095_0229ee24, obj, 8, 0xc0, 0xc0, 0x13f);
    return func_02002c6c((void *) data_ov095_0229ee40, obj, 8, 0x180, 0x180, 0x1ff);
}
