/* func_020a4740 @ 0x020a4740, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a1954(void *param1, void *param2, int param3);

extern unsigned char data_020e3c68[];

void func_020a4740(void *param0)
{
    unsigned char *ptr;
    ptr = (unsigned char *) param0;
    func_020a1954(ptr, (void *) data_020e3c68, 0x27);
    ptr[0xa1] = 0;
}
