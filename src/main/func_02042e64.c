/* func_02042e64 @ 0x02042e64, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_02045cec(int *, int);
extern int func_0204e414(void);
extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern void func_0204a330(int, int, int, int);

struct UnkStruct_02042e64 {
    unsigned short unk_00;
    unsigned short pad_02;
    signed short unk_04;
};

void func_02042e64(struct UnkStruct_02042e64 *p)
{
    int hi, lo;
    int arr[2];
    int ret, ret2;
    int v;
    unsigned short *p2;
    int h, l, llo, hlo;

    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (p->unk_04 > 0) {
        p->unk_04--;
    }
    if (p->unk_04 != 0) {
        return;
    }

    hi = p->unk_00 >> 8;
    lo = p->unk_00 & 0xff;
    arr[0] = hi;
    arr[1] = lo;

    ret = func_02045cec(arr, 0);
    if (ret >= 0) {
        return;
    }

    v = 0xe3;
    ret2 = func_0204e414();
    p->unk_04 = -1;
    if (ret2 != 0) {
        h = hi >> 4;
        l = lo >> 4;
        llo = lo - (l << 4);
        hlo = hi - (h << 4);
        p2 = func_0204f5e0(ret2, h, l, hlo, llo, 0);
        if (p2 != 0) {
            int val = *p2;
            int rem = (val - 0xe8) % 5;
            v = (unsigned short) (rem + 0xe3);
        }
    }

    func_0204a330(p->unk_00 >> 8, p->unk_00 & 0xff, v, 0);
}
