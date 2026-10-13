/* func_020bb6d8 @ 0x020bb6d8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(unsigned char *buf);
extern void func_020c1608(unsigned char *dst, unsigned char *src);
extern int func_020bb6b0(int a, int b);
extern int func_020bb75c(int a, int b);
extern signed char data_021f3b28[];
extern unsigned char data_021dc7a8[];

void func_020bb6d8(int self)
{
    unsigned char *base = data_021dc7a8;
    unsigned char buf[12];
    int status, t;

    ((unsigned int *) buf)[0] = 0;
    ((unsigned int *) buf)[1] = 0;
    func_0209e474(buf);

    if (((data_021f3b28[4] + 6) % 24) == buf[2]) {
        return;
    }

    func_020c1608(&base[0x1737e], buf);

    status = func_020bb6b0(self, 1);
    switch (status) {
        case 3:
        case 4:
            base[0x17385] = 1;
            break;
    }

    if (func_020bb75c(self, status) == 0) {
        return;
    }

    t = (int) buf[2] - 6;
    if (t < 0) {
        t += 24;
    }
    base[0x17384] = (unsigned char) t;
}
