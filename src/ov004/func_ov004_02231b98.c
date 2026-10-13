/* func_ov004_02231b98 @ 0x02231b98, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef union {
    unsigned short value;
    struct {
        unsigned short r : 5, g : 5, b : 5, a : 1;
    } bits;
} Color;
extern unsigned char *func_020ba4a0(void);
extern short func_020bbf00(int);
short func_ov004_02231b98(void)
{
    unsigned char *owner = func_020ba4a0();
    // Keep the observed halfword store/reload before the color copy.
    struct {
        volatile unsigned short temp;
        Color result, add;
    } sample;
    sample.result.value = 0xffff;
    if (owner) {
        int r, g, b;
        sample.temp = func_020bbf00(0);
        sample.add.value = sample.temp;
        sample.result.value = *(unsigned short *) (owner + 10);
        r = sample.result.bits.r + (int) sample.add.bits.r / 3;
        g = sample.result.bits.g + (int) sample.add.bits.g / 3;
        b = sample.result.bits.b + (int) sample.add.bits.b / 3;
        if (r > 31) {
            r = 31;
        } else if (r < 0) {
            r = 0;
        }
        if (g > 31) {
            g = 31;
        } else if (g < 0) {
            g = 0;
        }
        if (b > 31) {
            b = 31;
        } else if (b < 0) {
            b = 0;
        }
        sample.result.bits.r = r;
        sample.result.bits.g = g;
        sample.result.bits.b = b;
    }
    return *(short *) &sample.result;
}
