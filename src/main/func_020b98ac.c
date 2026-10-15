/* func_020b98ac @ 0x020b98ac, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ce0(void *param1, void *param2);

extern unsigned char data_021f6c98[];

void func_020b98ac(void *param1)
{
    void *r1 = param1;
    if (r1 != 0) {
        r1 = (char *) r1 + 4;
    }
    func_020e8ce0((void *) data_021f6c98, r1);
}
