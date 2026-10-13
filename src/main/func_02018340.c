/* func_02018340 @ 0x02018340, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern char data_021fbee8;
extern int func_02057c68(void *p);
extern void func_0201b1a4(void *p, void *q, int, int, int);
extern void func_0201b044(void *p, void *q);
extern void func_0201afd4(void *p, void *q);
extern void func_02016764(void *p, void *q, int, int, int, int, int, int);
extern void func_02012444(int, int, int);

void func_02018340(char *obj, char *src)
{
    unsigned short h;
    int v;

    if (func_02057c68(src) == 0) {
        return;
    }

    h = data_020c80f8;
    func_0201b1a4(src + 0x350, src, 0, 0, h);
    func_0201b044(src + 0x350, &data_021fbee8);
    func_0201afd4(src + 0x350, &data_021fbee8);
    func_02016764(src + 0x334, src, 0x25, h, 1, 0x1000, 0, 0);

    v = *(int *) (src + 0x628);
    if (v != 0) {
        func_02012444(v, h, 0);
    }

    *(unsigned char *) (obj + 0x98) = 2;
}
