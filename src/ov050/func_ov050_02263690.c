/* func_ov050_02263690 @ 0x02263690, 0x20 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern void func_020edb3c(void *);

extern unsigned char data_ov050_02265b14[];

void *func_ov050_02263690(void *p)
{
    *(void **) p = (void *) data_ov050_02265b14;
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}
