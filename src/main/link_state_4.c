/* link_state_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a6cd4 @ 0x020a6cd4, 0x10 bytes, Thumb
 * func_020a6cc4 @ 0x020a6cc4, 0x10 bytes, Thumb
 */

extern void func_020a5718(void *dst, const void *src);
extern unsigned char data_021f4320[];
extern unsigned char func_020a5710(void *p);

void func_020a6cd4(void *src)
{
    func_020a5718((void *) data_021f4320, src);
}

unsigned char func_020a6cc4(void)
{
    return func_020a5710((void *) data_021f4320);
}
