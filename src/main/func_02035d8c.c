/* func_02035d8c @ 0x02035d8c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035624(int arg);

typedef struct {
    unsigned char pad_00[8];
    unsigned char b0, b1, b2, b3;
    unsigned int w0;
    unsigned int w1;
} UnkStruct_02035d8c;

void func_02035d8c(UnkStruct_02035d8c *p)
{
    p->b0 = 0;
    p->b1 = 0;
    p->b2 = 0;
    p->b3 = 0;
    if (p->w0 != 0 || p->w1 != 0) {
        func_02035624(7);
        p->w0 = 0;
        p->w1 = 0;
    }
}
