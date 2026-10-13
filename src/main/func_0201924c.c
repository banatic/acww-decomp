/* func_0201924c @ 0x0201924c, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0201b040(void *);
extern void func_0201b188(void *, void *);
extern int func_0201aff8(void *, void *, int);
extern int func_0201afc0(void *);
extern void func_0201afd4(void *, unsigned int);
extern void func_02019af0(void *, int);
extern int func_0201c3b0(void *, short *, unsigned int);
extern int func_0201afe4(void *);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_0201aff4(void *, short);
extern void func_020123ec(unsigned int, unsigned int, int _x);
extern unsigned short data_020c80f8;

void func_0201924c(unsigned char *p0, unsigned char *p1)
{
    short local;
    unsigned int s;
    unsigned int tmp;
    unsigned int v;

    s = func_0201b040(p1 + 0x350);
    func_0201b188(p1 + 0x350, p1);
    if (func_0201aff8(p1 + 0x350, p1, 0) != 0) {
        if (func_0201afc0(p1 + 0x350) != 0) {
            func_0201afd4(p1 + 0x350, s);
        } else {
            func_02019af0(p0, 1);
        }
    } else {
        if (func_0201c3b0(p1, &local, s) == 0) {
            s = data_020c80f8;
            tmp = func_0201afe4(p1 + 0x350);
            func_0201b1a4(p1 + 0x350, p1, 3, tmp, data_020c80f8);
            func_0201aff4(p1 + 0x350, local);
            *(unsigned char *) (p0 + 0x98) = 0;
            *(unsigned int *) (p1 + 0x98) = 0;
            v = *(unsigned int *) (p1 + 0x628);
            if (v != 0) {
                func_020123ec(v, s, 0);
            }
        }
    }
}