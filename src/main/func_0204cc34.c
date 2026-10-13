/* func_0204cc34 @ 0x0204cc34, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef union {
    int words[2];
    unsigned char bytes[8];
} Buf;

extern int func_0209de88(int, int, int);
extern int func_020644cc(int);
extern void func_0209e29c(int, int);

void func_0204cc34(unsigned char *self, unsigned char *p)
{
    Buf buf;
    int firstResult;
    int loopResult;
    int counter;

    buf.words[0] = 0;
    buf.words[1] = 0;

    firstResult = func_0209de88(p[2], p[1], p[0]);

    counter = 7;
    do {
        loopResult = func_020644cc(counter);
    } while (loopResult == 1 || loopResult == 2);

    buf.words[0] = 0;
    buf.words[1] = 0;
    buf.bytes[5] = p[2];
    buf.bytes[4] = p[1];
    buf.bytes[3] = p[0];
    func_0209e29c((int) &buf, (7 - firstResult) + loopResult);

    self[0xa] = buf.bytes[5];
    self[9] = buf.bytes[4];
    self[8] = buf.bytes[3];
}
