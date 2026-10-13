/* func_02084d08 @ 0x02084d08, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e1ca8[];
extern void func_02084dc8(unsigned char *data, void *p0, void *p2, unsigned int p1, void *p3);

int func_02084d08(void *p0, unsigned int p1, void *p2, void *p3)
{
    if (data_020e1ca8[0xF] < p1) {
        func_02084dc8(data_020e1ca8, p0, p2, p1, p3);
        return 1;
    }
    return 0;
}
