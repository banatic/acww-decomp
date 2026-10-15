/* func_ov003_02213ae4 @ 0x02213ae4, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00[0xc];
    unsigned char data[3];
    unsigned char rest[0x11];
} Buffer;

extern unsigned int func_0200e92c(Buffer *buf);
extern void func_0200e90c(Buffer *buf, int a, unsigned int b, signed short c);
extern void *func_0200e894(void *obj, Buffer *buf);
extern int func_0200e91c(Buffer *buf);

void *func_ov003_02213ae4(void *obj, unsigned char b, unsigned char c, unsigned char d, unsigned int e, signed short f)
{
    Buffer buf;
    void *ret;

    func_0200e92c(&buf);
    func_0200e90c(&buf, 0x57, e, f);
    {
        unsigned char *p = buf.data;
        p[2] = b;
        p[0] = c;
        p[1] = d;
    }
    ret = func_0200e894(obj, &buf);
    func_0200e91c(&buf);
    return ret;
}
