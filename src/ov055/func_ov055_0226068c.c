/* func_ov055_0226068c @ 0x0226068c, 0x68 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209010c(void *);
extern void func_02090140(void *, int);
extern void *func_02090040(int);
extern void func_ov055_02260668(void *);
extern void MI_CpuCopy8(void *, const void *, int);

extern unsigned char data_021f37f4[];

void func_ov055_0226068c(void *p)
{
    void *r4;
    unsigned char b;

    r4 = func_02090040(4);
    b = ((unsigned char *) p)[0x1bc0];
    if (b == 2) {
        MI_CpuCopy8((void *) ((char *) p + 0x1abc), (const void *) data_021f37f4, 0x104);
        func_ov055_02260668(p);
    } else if (b == 1) {
        MI_CpuCopy8((void *) ((char *) p + 0x116c), r4, 0x950);
        func_0209010c(r4);
        func_02090140(r4, 1);
    }
}
