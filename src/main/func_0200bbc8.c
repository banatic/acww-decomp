/* func_0200bbc8 @ 0x0200bbc8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned char data_020e54a8;
extern void func_0200bda0(void *p, int *pairbuf, int *result);
extern void func_0200bdbc(void *self, int *pair, int a, int b, int c);

void func_0200bbc8(void *self, int param2)
{
    int cond = (data_020e54a8 == 1) ? 1 : 0;
    if (cond != 0) {
        return;
    }
    if (*(int *) ((char *) self + 0x7f0) == 0x18) {
        *(short *) ((char *) self + 0xc84) = (short) param2;
        return;
    }
    {
        int pairbuf[2];
        int result;
        pairbuf[0] = 0;
        pairbuf[1] = 0;
        func_0200bda0((char *) self + 0x8f0, pairbuf, &result);
        if (result >= 0) {
            return;
        } else {
            int pair[2];
            pair[0] = pairbuf[0];
            pair[1] = pairbuf[1];
            func_0200bdbc(self, pair, -1, 6, param2);
        }
    }
}
