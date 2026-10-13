/* func_020952ac @ 0x020952ac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003348(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3);

void func_020952ac(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    volatile unsigned int unused;
    unsigned int combined;

    unused = 0;
    combined = ((arg0 << 30) & 0xC0000000) | (arg3 & 0x3fffffff);
    func_02003348(9, combined, arg1, arg2);
}
