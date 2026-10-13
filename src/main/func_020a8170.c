/* func_020a8170 @ 0x020a8170, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, const void *src, unsigned int size);

extern unsigned char data_021f43ec;

void func_020a8170(void *arg0)
{
    unsigned char val;
    val = data_021f43ec;
    *(unsigned char *) ((char *) arg0 + 0x1e) = val;
    MI_CpuFill8((char *) arg0 + 4, 0, 0x1a);
}
