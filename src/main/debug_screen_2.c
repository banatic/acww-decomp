/* debug_screen_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001964 @ 0x02001964, 0x24 bytes, Thumb
 * func_02001910 @ 0x02001910, 0x54 bytes, Thumb
 * func_020018b4 @ 0x020018b4, 0x5c bytes, Thumb
 * func_0200184c @ 0x0200184c, 0x68 bytes, Thumb
 */

#define va_start(ap, last) ((ap) = (char *) ((((unsigned int) (&(last))) & ~3) + sizeof(last)))
#define va_end(ap) ((void) 0)

typedef char *va_list;

extern char data_020d34e0[];
extern void func_02001988(void *, int, const char *, va_list);
extern void *OS_GetDTCMAddress(void);
extern int OSi_MainExArenaEnabled;
extern void func_020b97b4(unsigned short *header, short *buffer, const char *format, ...);
extern unsigned char data_020d34d8;
extern void *data_0213fddc;
extern void *data_0213fde0;
extern void *data_0213fdd8;
extern char data_020d34cc[];

void func_02001964(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    func_02001988(data_020d34e0, 0, fmt, ap);
    va_end(ap);
}

int func_02001910(void *ptr, unsigned int len)
{
    char *p = (char *) ptr;
    char *end = p + len;
    char *A = (char *) OS_GetDTCMAddress();
    char *B = A + 0x4000;
    unsigned int C = OSi_MainExArenaEnabled ? 0x027e0000 : 0x023ff000;
    if ((unsigned int) p < 0x02000000) {
        goto L1;
    }
    if ((unsigned int) end <= C) {
        goto success;
    }
L1:
    if (A > p) {
        goto fail;
    }
    if (end > B) {
        goto fail;
    }
success:
    return 1;
fail:
    return 0;
}

void func_020018b4(void *param0, void *param1, unsigned int size)
{
    unsigned char *ptr;
    unsigned short tmp[2];
    unsigned short val;
    unsigned char *ptr2;
    unsigned char *p;
    unsigned char *end;

    tmp[0] = 0xD000;
    tmp[1] = 0xD000;
    ptr = (unsigned char *) param1;
    val = 0xD000;
    p = ptr;
    end = p + (size & ~3u);
    p = (unsigned char *) (((unsigned int) p) & ~3u);
    ptr2 = end;
    while (p < ptr2) {
        if (func_02001910((void *) p, 4) == 0) {
            break;
        }
        tmp[1] = val;
        func_020b97b4(tmp, param0, (const char *) &data_020d34d8, *((unsigned int *) p));
        param0 = ((char *) param0) + 0x10;
        val = (unsigned short) (val ^ 0x3000);
        p += 4;
    }
}

void func_0200184c(void)
{
    unsigned short buf[2];
    void *p4;
    void *p5;

    p4 = data_0213fddc;
    buf[0] = 0xd000;
    buf[1] = 0xd000;

    if (data_0213fde0) {
        p5 = *(void **) ((char *) data_0213fde0 + 0x38);
    } else {
        p5 = data_0213fdd8;
    }

    func_020b97b4(buf, (short *) ((char *) p4 + 0x40), data_020d34cc, p5);
    if (func_02001910(p5, 4)) {
        p4 = (char *) p4 + 0x80;
        func_020018b4(p4, p5, 0x160);
    }
}
