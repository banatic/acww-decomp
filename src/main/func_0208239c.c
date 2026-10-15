/* func_0208239c @ 0x0208239c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021e5a2c;
extern void *func_020824d0(const void *p);
extern int func_0207cec0(const void *p, unsigned int low);
extern int func_020808d0(unsigned int);

typedef struct {
    unsigned short flags;
} S_0208239c;

int func_0208239c(const S_0208239c *p)
{
    unsigned short raw = p->flags;
    unsigned int low = raw & 0xfff;
    int ret = 0;
    int kind = (raw & 0xf000) >> 12;

    if (kind != 0xd) {
        if (kind == 0xe) {
            int tmp = func_0207cec0(&data_021e5a2c, low);
            if (tmp) {
                ret = func_020808d0((unsigned int) tmp);
            }
        }
    } else {
        void *q = func_020824d0(p);
        if (q) {
            ret = ((unsigned char *) q)[2];
        }
    }
    return ret;
}
