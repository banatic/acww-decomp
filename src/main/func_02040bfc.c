/* func_02040bfc @ 0x02040bfc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
    unsigned char unk_03;
} Result_02040bfc;

extern int func_0203fae4(void);
extern void func_0209e474(void *buf8);
extern int data_021c7584;
extern void *func_02040980(void *context);
extern void MI_CpuCopy8(void *a, void *b, int n);
extern int func_0203fcb4(int a, void *b, int c);
extern void func_020408a8(Result_02040bfc *result);
extern int data_021dc7a8;

void func_02040bfc(void)
{
    int buf8[2];
    unsigned char buf8b[8];
    unsigned char v;
    unsigned char f2;
    unsigned char f3;
    Result_02040bfc *result;
    int rv;
    unsigned char *base;

    if (func_0203fae4() == 1) {
        return;
    }

    base = (unsigned char *) &data_021dc7a8;

    buf8[0] = 0;
    buf8[1] = 0;
    func_0209e474(buf8);
    v = ((unsigned char *) buf8)[2];
    if (data_021c7584 == v) {
        return;
    }
    data_021c7584 = v;

    result = func_02040980(base + 0x17218);
    if (result == 0) {
        return;
    }
    f2 = result->unk_02;
    if (f2 == 0x63) {
        return;
    }

    MI_CpuCopy8(buf8, buf8b, 8);
    rv = func_0203fcb4(f2, buf8b, 0);

    f3 = result->unk_03;
    switch (f3) {
        case 0:
            if (rv == 2) {
                result->unk_03 = 1;
            }
            break;
        case 1:
            if (rv == 0) {
                func_020408a8(result);
            }
            break;
        default:
            break;
    }
}
