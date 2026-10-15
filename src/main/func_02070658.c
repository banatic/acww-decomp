/* func_02070658 @ 0x02070658, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern unsigned char data_020e54a8;
extern int data_020c904c;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void func_02077978(unsigned char *src, int *out1, int *out2);
extern int func_ov003_0222780c(unsigned char k, unsigned short idx, Pair *pr);
extern void func_ov003_0222c3a8(Pair *pr, unsigned char k);

void func_02070658(unsigned char *p, int arg)
{
    unsigned char buf[5];
    Pair pr;
    int extra;
    unsigned int flag;
    unsigned char k;
    unsigned short idx;

    if (data_020e54a8 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag == 0) {
        return;
    }
    k = (unsigned char) arg;
    MI_CpuCopy8(p + 2, buf, 5);
    func_02077978(buf, &pr.a, &extra);
    pr.b = data_020c904c;
    if (p[0] == 2) {
        if (p[1] < 0x38) {
            idx = (unsigned short) (p[1] + 0x12e8);
        } else {
            idx = 0x12e8;
        }
        func_ov003_0222780c(k, idx, &pr);
    } else {
        func_ov003_0222c3a8(&pr, k);
    }
}
