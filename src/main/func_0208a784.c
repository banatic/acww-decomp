/* func_0208a784 @ 0x0208a784, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051ad8(void *p);
extern void func_0208a4dc(void *p);

void func_0208a784(void *p)
{
    unsigned int *u32 = (unsigned int *) p;
    unsigned char *u8 = (unsigned char *) p;
    u32[0x34 >> 2] = 0;
    u32[0x38 >> 2] = 0;
    u32[0x3c >> 2] = 0;
    u32[0x40 >> 2] = 0;
    u32[0x44 >> 2] = -1;
    u32[0x48 >> 2] = 0;
    u32[0x4c >> 2] = 0;
    u32[0x50 >> 2] = 0;
    u8[0x54] = 0;
    u8[0x55] = 0;
    u8[0x57] = 0;
    u8[0x58] = 0;
    u8[0x59] = 0;
    u8[0x5a] = 0;
    u8[0x5b] = 0;
    u8[0x5c] = 0;
    func_02051ad8((char *) p + 0x60);
    func_02051ad8((char *) p + 0x90);
    *(unsigned int *) ((char *) p + 0xc8) = 0;
    func_0208a4dc(p);
}
