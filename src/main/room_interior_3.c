/* room_interior_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02034b80 @ 0x02034b80, 0x54 bytes, Thumb
 * func_02034b58 @ 0x02034b58, 0x28 bytes, Thumb
 * func_02034b04 @ 0x02034b04, 0x54 bytes, Thumb
 * func_02034adc @ 0x02034adc, 0x28 bytes, Thumb
 */

extern unsigned char data_020e54a8;
extern int func_ov004_022321b8(void *, int, int);
extern void func_02034bd4(void *, int, int, int);
extern void func_02034c64(void *, void *);
extern char data_021c5174[];
void *func_ov004_02232104(void *a, void *b, void *c);

int func_02034b80(unsigned short *self, int a, int b, int c)
{
    unsigned short t = *self;
    unsigned int flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag > 0) {
        int r = func_ov004_022321b8(&t, a, b);
        if (c) {
            func_02034bd4(&t, a, 1, b);
        }
        return r;
    } else {
        return (int) ((int *) data_021c5174);
    }
}

void func_02034b58(void *a1, void *a2, void *a3, void *a4)
{
    void *sp;

    func_02034c64(&sp, a1);
    func_02034b80((unsigned short *) (&sp), (int) a2, (int) a3, (int) a4);
}

void *func_02034b04(unsigned short *src, void *p1, void *p2, unsigned int flag)
{
    unsigned short local;
    unsigned int cond;

    local = *src;
    cond = (data_020e54a8 == 1);
    if (cond > 0) {
        void *result;
        result = func_ov004_02232104(&local, p1, p2);
        if (flag != 0) {
            func_02034bd4(&local, (int) p1, 0, (int) p2);
        }
        return result;
    } else {
        return data_021c5174;
    }
}

void func_02034adc(void *a, void *b, void *c, void *d)
{
    void *sp;
    func_02034c64(&sp, a);
    func_02034b04((unsigned short *) (&sp), b, c, (unsigned int) d);
}
