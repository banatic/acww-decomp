/* func_02072204 @ 0x02072204, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064af4(void *dst, const void *src, unsigned int size);
extern unsigned char data_020e17f0[];

void func_02072204(unsigned char *src)
{
    func_02064af4(data_020e17f0, src, 0x1000);
}
