/* func_020a4b54 @ 0x020a4b54, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a1954(void *dst, const void *src, unsigned int size);
extern void func_0203d394(void);

extern unsigned char data_020e3c54[];

void func_020a4b54(void *param)
{
    unsigned char *p;

    func_020a1954(param, (const void *) data_020e3c54, 0x28);
    func_0203d394();
    p = (unsigned char *) param + 0xa1;
    *p = 0;
}
