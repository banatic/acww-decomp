/* func_020a753c @ 0x020a753c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Hdr {
    unsigned short total;
    unsigned short len;
    unsigned char kind;
    unsigned char pad_05[3];
} Hdr;

extern void *data_020ccf94;
extern unsigned char *func_02073424(void *);
extern void func_02073410(void *);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void (*data_020d1c34[])(unsigned char *, unsigned int);

void func_020a753c(void)
{
    void *h;
    unsigned char *p;
    unsigned int off;
    unsigned int total;
    unsigned int len;
    unsigned int k;
    Hdr hdr;
    h = data_020ccf94;
    p = func_02073424(h);
    MI_CpuCopy8(p, &hdr, 2);
    total = hdr.total;
    off = 0;
    p += 2;
    off += 2;
    while (off < total) {
        MI_CpuCopy8(p, &hdr.len, 4);
        p += 4;
        off += 4;
        len = hdr.len;
        k = *(volatile unsigned char *) &hdr.kind;
        data_020d1c34[k](p, len);
        p += len;
        off += len;
    }
    func_02073410(h);
}
