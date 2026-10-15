/* func_02075450 @ 0x02075450, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern char *func_020738e4(int);
extern int data_020ccf94;

void func_02075450(unsigned char *payload, unsigned int length, int player)
{
    int local;
    char *ret;

    MI_CpuCopy8(payload, &local, 4);
    ret = func_020738e4(data_020ccf94);
    MI_CpuCopy8(payload + 4, ret + local, length - 4);
}
