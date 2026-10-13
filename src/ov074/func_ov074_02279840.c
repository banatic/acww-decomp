/* func_ov074_02279840 @ 0x02279840, 0x38 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern void func_ov074_02278af8(void *a, void *b, void *c);
extern void func_ov074_02279778(void *a, int b);

extern unsigned char data_021fbe94[];

int func_ov074_02279840(void *self)
{
    if (func_0202ec58() == 0) {
        return 0;
    }
    func_ov074_02278af8((char *) self + 0x714, *(void **) data_021fbe94, (char *) self + 0xec);
    func_ov074_02279778(self, 3);
    return 1;
}
