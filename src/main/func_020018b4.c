/* func_020018b4 @ 0x020018b4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02001910(const void *p, int len);
extern void func_020b97b4(void *buf, void *param0, void *global, unsigned int word);
extern unsigned char data_020d34d8;

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
        if (func_02001910(p, 4) == 0) {
            break;
        }
        tmp[1] = val;
        func_020b97b4(tmp, param0, &data_020d34d8, *((unsigned int *) p));
        param0 = ((char *) param0) + 0x10;
        val = (unsigned short) (val ^ 0x3000);
        p += 4;
    }
}
