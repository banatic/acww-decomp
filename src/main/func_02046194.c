/* func_02046194 @ 0x02046194, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c7884[];
extern void func_02046518(unsigned char *ptr, unsigned int arg1, unsigned short packed, unsigned int arg4, unsigned short a5,
                          unsigned char a6, unsigned char a7, unsigned char a8, unsigned char a9, unsigned char a10,
                          signed char a11);

struct Src {
    int a;
    int b;
};

void func_02046194(unsigned int idx, unsigned int arg1, struct Src *src, unsigned int arg4, unsigned short a5,
                   unsigned char a6, unsigned char a7, unsigned char a8, unsigned char a9, unsigned char a10, signed char a11)
{
    unsigned short packed;

    ((unsigned char *) &packed)[1] = (unsigned char) src->a;
    ((unsigned char *) &packed)[0] = (unsigned char) src->b;

    func_02046518(&data_021c7884[idx << 4], arg1, packed, arg4, a5, a6, a7, a8, a9, a10, a11);
}
