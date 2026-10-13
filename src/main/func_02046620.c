/* func_02046620 @ 0x02046620, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02042ce8(void *);
extern void func_02045b3c(void *);

extern unsigned char data_021c7880[];
extern unsigned char data_021c7c48[];

void func_02046620(void)
{
    func_02042ce8((void *) data_021c7c48);
    func_02045b3c((void *) data_021c7880);
}
