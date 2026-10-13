/* func_02052b20 @ 0x02052b20, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char lo : 6;
    unsigned char f6 : 1;
    unsigned char f7 : 1;
} SomeBits;

typedef union {
    unsigned char byte;
    SomeBits bits;
} Some;

extern unsigned char data_021ebcd4;
extern void *data_020ccf94;

extern void func_02060bf8(void *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, unsigned char *, int);
extern void func_02073770(void *, int, int);

void func_02052b20(Some *p)
{
    int x;
    int y;

    x = p->bits.lo;
    y = p->bits.f6 != 0;

    if (p->bits.f7 == 1) {
        void *o;
        unsigned char tmp;

        func_02060bf8(&data_021ebcd4, x, y);

        tmp = p->byte;
        tmp &= ~0x80;
        o = data_020ccf94;

        func_02073820(o);
        func_020737f0(o, &tmp, 1);
        func_02073770(o, 0x19, 4);
    } else {
        func_02060bf8(&data_021ebcd4, x, y);
    }
}
