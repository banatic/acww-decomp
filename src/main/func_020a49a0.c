/* func_020a49a0 @ 0x020a49a0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a1954(void *dst, const void *src, unsigned int size);
extern unsigned char data_020e3c54[12];

void func_020a49a0(unsigned char *param0)
{
    unsigned char *p;

    func_020a1954(param0, data_020e3c54, 12);
    p = param0 + 0xa1;
    *p = 0;
}
