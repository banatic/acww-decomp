/* func_0206ef98 @ 0x0206ef98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f170(void);
extern void func_0206fcd4(void);

extern unsigned char data_021cfc10[];
extern unsigned char data_021cfc20[];

void func_0206ef98(void)
{
    unsigned short *p_short;
    unsigned char *p_byte;

    func_0206f170();
    p_short = (unsigned short *) data_021cfc20;
    *p_short = 1;
    p_byte = (unsigned char *) data_021cfc10;
    *p_byte = 4;
    func_0206fcd4();
}
