/* func_0209dfc0 @ 0x0209dfc0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void RTC_Init(int param);
extern void func_0209e49c(int param);

extern unsigned char data_021dc744[];

void func_0209dfc0(int param)
{
    RTC_Init(param);
    func_0209e49c((unsigned int) data_021dc744);
}
