/* func_02010b50 @ 0x02010b50, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d7b8(unsigned char *, unsigned int, int, int);
extern unsigned int func_0205d8a0(unsigned char *);
extern void func_0205678c(unsigned char *, unsigned int, int, int, unsigned int, unsigned int);
extern void func_02056778(unsigned char *);

void func_02010b50(unsigned char *base, unsigned int *src, unsigned char *src_byte)
{
    unsigned int result;

    func_0205d7b8(base + 0x70e, *src, 1, 0);
    result = func_0205d8a0(base + 0x70e);
    func_0205678c(base + 0x710, result, 0, 0, *src_byte, 0x1000);
    func_02056778(base + 0x710);
    *(unsigned int *) (base + 0x76c) = *src;
}
