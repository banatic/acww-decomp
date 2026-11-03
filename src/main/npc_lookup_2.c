/* npc_lookup_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208249c @ 0x0208249c, 0x34 bytes, Thumb
 * func_02082438 @ 0x02082438, 0x64 bytes, Thumb
 * func_020823e8 @ 0x020823e8, 0x50 bytes, Thumb
 * func_0208239c @ 0x0208239c, 0x4c bytes, Thumb
 */

typedef struct {
    unsigned short flags;
} S_0208239c;

extern int func_0200363c(int x);
extern int func_020b4a20(void *dst, void *src, const void *fmt);
extern const char data_020e19c8[];
extern int func_0207cec0(void *p, int);
extern void *func_0208150c(unsigned int object);
extern int func_02003618(void *ptr, void *a);
extern int data_020e19b8;
extern int func_0200364c(void *ptr);
extern void *func_020824d0(unsigned short *p);
extern unsigned char data_021e5a2c[];
extern int func_020808d0(unsigned int);

int func_0208249c(char *arg0, int arg1)
{
    int result = 0;
    char local;

    if (func_0200363c(arg1)) {
        local = (char) arg1;
        func_020b4a20(arg0, &local, data_020e19c8);
        result = 1;
    }

    return result;
}

int func_02082438(void *a, unsigned short *b)
{
    int forwarded_value;

    unsigned short v = *b;
    int low = v & 0xfff;
    int result = 0;
    int high = (v & 0xf000) >> 12;

    if (high != 13) {
        if (high == 14) {
            if ((forwarded_value = (int) func_0207cec0(((int *) data_021e5a2c), low))) {
                result = func_02003618(func_0208150c((unsigned int) forwarded_value), a);
            }
        }
    } else {
        if (low < 0x26) {
            unsigned char c = (unsigned char) low;
            func_020b4a20(a, (void *) (&c), (const void *) (&data_020e19b8));
            result = 1;
        }
    }
    return result;
}

int func_020823e8(unsigned short *p)
{
    unsigned short v = *p;
    int low12 = v & 0xfff;
    int type = (v & 0xf000) >> 12;
    int result = 5;
    switch (type) {
        case 14: {
            void *r = (void *) func_0207cec0((void *) data_021e5a2c, low12);
            if (r) {
                result = func_0200364c(func_0208150c((unsigned int) r));
            }
            break;
        }
        case 13: {
            void *r = func_020824d0(p);
            if (r) {
                result = *(((unsigned char *) r) + 1);
            }
            break;
        }
    }
    return result;
}

int func_0208239c(const S_0208239c *p)
{
    unsigned short raw = p->flags;
    unsigned int low = raw & 0xfff;
    int ret = 0;
    int kind = (raw & 0xf000) >> 12;

    if (kind != 0xd) {
        if (kind == 0xe) {
            int tmp = func_0207cec0((void *) (((unsigned char *) data_021e5a2c)), low);
            if (tmp) {
                ret = func_020808d0((unsigned int) tmp);
            }
        }
    } else {
        void *q = func_020824d0((unsigned short *) p);
        if (q) {
            ret = ((unsigned char *) q)[2];
        }
    }
    return ret;
}
