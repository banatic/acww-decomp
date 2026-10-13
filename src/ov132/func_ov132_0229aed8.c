/* func_ov132_0229aed8 @ 0x0229aed8, 0x2c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov132_0229b904[];
extern void *func_ov002_0220a768(void *, int);

void *func_ov132_0229aed8(void *self)
{
    unsigned char idx = ((unsigned char *) self)[0x1502];
    if (idx == 2) {
        return func_ov002_0220a768((char *) self + 0xf8, 6);
    }
    return data_ov132_0229b904[idx];
}
