/* func_020ade78 @ 0x020ade78, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b;
    unsigned char pad_01;
    unsigned short h;
} Hdr;

extern int func_02073d90(void *);
extern void *func_020984e8(void);
extern void *func_020996a0(void *);
extern unsigned short *func_020adf50(void *record);
extern unsigned int func_020adde4(unsigned short);
extern int func_02099020(void *, int);
extern void func_02066694(void *);
extern void *func_02099870(void *);
extern void func_02066024(void *, Hdr *, void *, void *, void *, void *);
extern unsigned short func_02065ed0(void *, unsigned short, int);
extern int func_020979f0(void *, int);
extern void func_02098ff8(void *, int);
extern void func_02066688(void *);
extern void *data_020ccf94;
extern const unsigned short data_020d1e34[];

extern unsigned char data_020e4150[];
extern unsigned char data_020e4154[];
extern unsigned char data_020e4190[];

void func_020ade78(void)
{
    int zero;
    Hdr hdr;
    char buf[0x104];
    void *h;
    unsigned int i, n;
    int id;

    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    h = func_020984e8();
    if (h == 0) {
        return;
    }
    n = func_020adde4(*func_020adf50(func_020996a0(h)));
    if (n == 0) {
        return;
    }
    zero = 0;
    for (i = 0; i < n; i++) {
        id = i + 0x1c;
        if (i < 4 && func_02099020(h, id) == 0) {
            func_02066694(buf);
            hdr.b = (unsigned char) i;
            func_02066024(buf, &hdr, (void *) data_020e4190, (void *) data_020e4150, (void *) data_020e4154, func_02099870(h));
            func_02065ed0(buf, data_020d1e34[i & 3], 1);
            if (func_020979f0(buf, zero) != 0) {
                func_02098ff8(h, id);
            }
            func_02066688(buf);
        }
    }
}
