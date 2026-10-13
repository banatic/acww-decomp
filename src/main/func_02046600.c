/* func_02046600 @ 0x02046600, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02042cd8(void *);
extern void func_02042218(void *);

extern unsigned char data_021c776c[];
extern unsigned char data_021c7c48[];

void func_02046600(void)
{
    func_02042cd8((void *) data_021c7c48);
    func_02042218((void *) data_021c776c);
}
