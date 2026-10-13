/* func_ov095_0229b16c @ 0x0229b16c, 0x20 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov095_0229e424[];
extern char data_ov095_0229ea84;

struct Example {
    char pad_00[0x16];
    unsigned char unk_16;
};

void *func_ov095_0229b16c(struct Example *self)
{
    unsigned char idx;
    void *val;

    idx = self->unk_16;
    if (idx >= 5) {
        return 0;
    }
    val = data_ov095_0229e424[idx];
    if (val != 0) {
        return val;
    }
    return (void *) &data_ov095_0229ea84;
}
