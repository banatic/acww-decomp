/* func_02070614 @ 0x02070614, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, unsigned int len);

extern unsigned char data_021f3a68[];
extern unsigned char data_021f3a86[];

void func_02070614(unsigned char *p, int player)
{
    char buf[30];
    MI_CpuCopy8(p + 1, buf, 30);
    switch (*p) {
        case 3:
            MI_CpuCopy8(buf, (const void *) data_021f3a68, 30);
            break;
        case 4:
            MI_CpuCopy8(buf, (const void *) data_021f3a86, 30);
            break;
    }
}
