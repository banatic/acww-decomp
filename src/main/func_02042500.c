/* func_02042500 @ 0x02042500, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void func_0209e100(void *, int);
extern int func_02042730(void *, void *, void *);
extern void func_0209e140(void *, int);
extern int func_0209de88(int, int, int);
extern void func_020426d8(void *, void *, void *);
extern void func_020425a8(void *, void *, int, void *, int);
extern int func_02098880(void *);
extern int func_0203fae4(void);
extern void func_02042684(void *, void *, void *);

extern unsigned char data_021dc7a8[]; // 0x021dc7a8
extern unsigned char data_021f3a64[]; // 0x021f3a64
extern unsigned char data_021c7768[]; // 0x021c7768

void func_02042500(void)
{
    unsigned char local[8];
    unsigned char *pA = data_021dc7a8;
    unsigned char *pB;
    int ret;
    int r;

    *(unsigned int *) &local[0] = 0;
    *(unsigned int *) &local[4] = 0;

    func_0209e474(local);
    func_0209e100(local, 6);
    pB = data_021f3a64;
    ret = func_02042730(data_021c7768, pB, local);
    if (ret != 0) {
        pB[2] = local[5];
        pB[1] = local[4];
        pB[0] = local[3];
        func_0209e140(local, ret - 1);
        r = func_0209de88(local[5], local[4], local[3]);
        func_020426d8(data_021c7768, pA, local);
        func_020425a8(data_021c7768, pA, ret, local, r);
    } else {
        if (pA[0x17276] == 0) {
            if (func_02098880(pA + 0x14) > 1 || func_0203fae4() == 0) {
                func_02042684(data_021c7768, pA, local);
            }
        }
    }
}
