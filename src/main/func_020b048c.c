/* func_020b048c @ 0x020b048c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b;
    unsigned char pad_01;
    unsigned short h;
} Hdr;

extern void *func_020984e8(void);
extern void func_02066694(void *);
extern void func_02062f90(void *, void *);
extern void func_0203d7c4(int, void *);
extern void *func_02099870(void *);
extern void func_02066024(void *, void *, void *, void *, void *, void *);
extern void func_02065ed0(void *, unsigned short, int);
extern void func_020979f0(void *, int);
extern void func_02062f4c(void *);
extern void func_02066688(void *);
extern const unsigned short data_020d1e74[];

extern unsigned char data_020e41d4[];
extern unsigned char data_020e41d8[];
extern unsigned char data_020e41dc[];

void func_020b048c(unsigned int idx)
{
    Hdr hdr;
    char a[0x28];
    char b[0x100];
    void *h;

    if (idx >= 0xd) {
        return;
    }
    hdr.h = data_020d1e74[idx];
    h = func_020984e8();
    if (h == 0) {
        return;
    }
    func_02066694(b);
    hdr.b = (unsigned char) idx;
    func_02062f90(a, &hdr.h);
    func_0203d7c4(1, a);
    func_02066024(b, &hdr, (void *) data_020e41dc, (void *) data_020e41d4, (void *) data_020e41d8, func_02099870(h));
    func_02065ed0(b, hdr.h, 1);
    func_020979f0(b, 0);
    func_02062f4c(a);
    func_02066688(b);
}
