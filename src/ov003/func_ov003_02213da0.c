/* func_ov003_02213da0 @ 0x02213da0, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032adc(void *);
extern int func_020311bc(void *, void *, void *, int);
extern void func_0200f27c(void *, int);
extern void func_0200f328(void *, int);
extern void func_0205eae0(void *, int, int, int);
extern int func_02056f28(void *, int);
extern void func_0204f818(int *, int *, void *);
extern void func_0204489c(int *);
extern void func_02032acc(void *);
extern int func_02073908(unsigned int *, unsigned int);
extern void func_02034270(void *, void *, int, int);
extern void func_0203423c(void *);
extern void func_020912d4(int, void *, int, int);

typedef unsigned char u8;
typedef unsigned int u32;

extern u32 *data_020ccf94;

struct UnkStruct_02213da0 {
    u8 pad_00[0x2d0];
    u8 unk_2D0[8];
    struct {
        unsigned int : 12;
        unsigned int f16 : 16;
        unsigned int : 4;
    } bf;
    u32 pad_2DC;
    u32 unk_2E0;
    u8 pad_2E4[0x5a0 - 0x2e4];
    u8 unk_5A0[0x800 - 0x5a0];
    u32 unk_800;
};

int func_ov003_02213da0(struct UnkStruct_02213da0 *p, void *a, u32 *src, u32 *dst)
{
    u8 buf[0x54];
    int tmp0, tmp1, out[2];

    func_02032adc(buf);
    if (func_020311bc(buf, dst, a, 0x1b) != 0) {
    main:
        func_0200f27c(p, 9);
        func_0200f328(p, 0x846);
        p->unk_2E0 = 0;
        func_0205eae0(&p->unk_5A0[0], 4, 3, 1);
        if (func_02056f28(&p->unk_2D0[0], 5) != 0) {
            tmp0 = 0;
            tmp1 = 0;
            func_0204f818(&tmp0, &tmp1, dst);
            out[0] = tmp0;
            out[1] = tmp1;
            func_0204489c(out);
        }
        if (p->bf.f16 > 4) {
            goto exit0;
        }
        func_02032acc(buf);
        return 1;
    } else {
        if (func_02056f28(&p->unk_2D0[0], 5) == 0) {
            goto exit0;
        }
        if (func_02073908(data_020ccf94, p->unk_800) != 0) {
            goto error;
        }
        func_02034270(&buf[0x14], src, 0, 0);
        if (*(u32 *) &buf[0x44] == 0) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            func_0203423c(&buf[0x14]);
            goto main;
        }
        func_0203423c(&buf[0x14]);
        goto error;
    }
error:
    func_020912d4(0xb, src, 0, 0);
    func_0200f27c(p, 9);
    func_0205eae0(&p->unk_5A0[0], 4, 3, 1);
exit0:
    func_02032acc(buf);
    return 0;
}