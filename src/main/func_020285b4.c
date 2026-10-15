/* func_020285b4 @ 0x020285b4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0202d9c4(unsigned int *);
extern void func_0209bd5c(void *);
extern void func_0207b57c(void *ptr);

extern unsigned char data_021e5a2c[];

void func_020285b4(unsigned int *argument0)
{
    func_0209bd5c((void *) func_0202d9c4((unsigned int *) argument0));
    func_0207b57c((void *) data_021e5a2c);
}
