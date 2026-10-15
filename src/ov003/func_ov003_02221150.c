/* func_ov003_02221150 @ 0x02221150, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *, int *, int);
extern int func_02045cec(int *, int);
extern void *func_02045bac(int index);
extern int func_ov003_0222139c(const void *, int, int *, int *, int, unsigned short, int, int);
extern char data_ov003_0223cfe4;

void func_ov003_02221150(int a0, int a1)
{
    int out[2];
    int copy[2];
    int pos[2];
    int extra[3];
    unsigned short flag;
    int index;

    out[0] = 0;
    out[1] = 0;
    flag = 0xfff1;
    func_0204f818(&out[0], &out[1], a1);

    copy[0] = out[0];
    copy[1] = out[1];

    if ((index = func_02045cec(copy, 0)) >= 0) {
        void *q = func_02045bac(index);
        if (q != 0) {
            flag = *(unsigned short *) ((char *) q + 0xa);
        }
    }

    extra[0] = 0;
    extra[1] = 0;
    extra[2] = 0;
    pos[0] = out[0];
    pos[1] = out[1];

    func_ov003_0222139c(&data_ov003_0223cfe4, a0, pos, extra, 3, flag, 0, 0);
}
