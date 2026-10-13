/* func_ov105_0229e1cc @ 0x0229e1cc, 0x64 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void RtcSendPxiCommand(int);
extern void func_ov002_02209114(void *, unsigned char, int);
extern void func_ov002_02208098(void *, int);

void func_ov105_0229e1cc(void *base)
{
    int flag;

    if (func_0208e484((char *) base + 0x24A4) == 0) {
        return;
    }

    *((unsigned char *) ((char *) base + 0x2BE)) =
        *((unsigned char *) ((char *) base + *((unsigned char *) ((char *) base + 0x2BF)) + 0x28F5));
    flag = 1;
    if (*((unsigned char *) ((char *) base + 0x2BE)) == 2) {
        flag = 0;
        RtcSendPxiCommand(0x24);
    }
    func_ov002_02209114((char *) base + 0x2508, *((unsigned char *) ((char *) base + 0x2BF)), flag);
    func_ov002_02208098(base, 0x17);
}
