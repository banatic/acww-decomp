/* func_0200184c @ 0x0200184c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_0213fddc;
extern void *data_0213fde0;
extern void *data_0213fdd8;
extern char data_020d34cc[];

extern void func_020b97b4(void *a, void *b, void *c, void *d);
extern int func_02001910(void *a, int b);
extern void func_020018b4(void *a, void *b, int c);

void func_0200184c(void)
{
    unsigned short buf[2];
    void *p4;
    void *p5;

    p4 = data_0213fddc;
    buf[0] = 0xd000;
    buf[1] = 0xd000;

    if (data_0213fde0) {
        p5 = *(void **) ((char *) data_0213fde0 + 0x38);
    } else {
        p5 = data_0213fdd8;
    }

    func_020b97b4(buf, (char *) p4 + 0x40, data_020d34cc, p5);
    if (func_02001910(p5, 4)) {
        p4 = (char *) p4 + 0x80;
        func_020018b4(p4, p5, 0x160);
    }
}
