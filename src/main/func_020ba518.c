/* func_020ba518 @ 0x020ba518, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205bfd0(void *a, void *b, void *c);
extern void func_02001b34(int a);

extern unsigned char data_021f6d2c[];
extern void func_01ffcd4c(void);
extern void func_020bab74(void);

void func_020ba518(void)
{
    func_0205bfd0((void *) data_021f6d2c, (void *) func_01ffcd4c, (void *) func_020bab74);
    func_02001b34(0xa);
}
