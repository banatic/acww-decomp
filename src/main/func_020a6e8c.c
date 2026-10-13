/* func_020a6e8c @ 0x020a6e8c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a635c(void *dst, const void *src, unsigned int size);
extern unsigned char data_021f4320[];

void func_020a6e8c(unsigned char *param0, unsigned char *param1)
{
    unsigned char *dst;
    unsigned char *src;

    dst = param0;
    src = param1;
    func_020a635c(data_021f4320, dst, (unsigned int) src);
}
