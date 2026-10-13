/* func_0204e938 @ 0x0204e938, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b7098(unsigned int);
extern void func_020b0698(unsigned int);

extern unsigned char data_021f3b56[];

void func_0204e938(unsigned int arg)
{
    unsigned int tmp;
    unsigned char *p;

    tmp = func_020b7098(arg);
    p = (unsigned char *) (arg + 0x2224);
    *p = (*p & ~0xFC) | (((unsigned char) tmp & 0x3F) << 2);
    func_020b0698((unsigned int) data_021f3b56);
}
