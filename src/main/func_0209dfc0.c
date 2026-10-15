/* func_0209dfc0 @ 0x0209dfc0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void RTC_Init(void);
extern void func_0209e49c(int param);

extern unsigned char data_021dc744[];

void func_0209dfc0(void)
{
    RTC_Init();
    func_0209e49c((unsigned int) data_021dc744);
}
