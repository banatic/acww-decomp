/* func_ov004_022461c4 @ 0x022461c4, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern unsigned short *func_020ae8e4(void *, unsigned int, unsigned short *);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_ov004_02246848(unsigned short *);
extern int func_ov004_02246650(void *, unsigned short *, int);
}
extern unsigned char data_021f3b44[];

static inline bool is_empty(unsigned short *p)
{
    if (func_0204bcdc(p)) {
        unsigned short empty = 0xfff1;
        return func_0204bc64(p) == func_0204bc64(&empty);
    } else {
        return *p == 0xfff1;
    }
}

extern "C" void func_ov004_022461c4(void *self)
{
    unsigned int i;
    for (i = 0; i < 6; ++i) {
        unsigned short item = 0xfff1;
        unsigned short *p = func_020ae8e4((void *) data_021f3b44, i, &item);
        if (!is_empty(p) && !is_empty(&item)) {
            func_ov004_02246650(self, p, func_ov004_02246848(&item));
        }
    }
}
