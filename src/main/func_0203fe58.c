/* func_0203fe58 @ 0x0203fe58, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *p);
extern void MI_CpuCopy8(void *dst, void *src, unsigned int n);
extern int func_0203fec4(void *p, void *q, int n);
extern unsigned char data_021c74d4[];
extern unsigned char data_021c74d0[];

void func_0203fe58(int param)
{
    unsigned int local0[2];
    unsigned char local1[8];

    local0[0] = 0;
    local0[1] = 0;

    func_0209e474(local0);
    MI_CpuCopy8(local0, local1, 8);
    func_0203fec4(data_021c74d4, local1, param);

    data_021c74d0[2] = ((unsigned char *) local0)[5];
    data_021c74d0[1] = ((unsigned char *) local0)[4];
    data_021c74d0[0] = ((unsigned char *) local0)[3];
}
