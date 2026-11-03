/* event_calendar: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203fd38 @ 0x0203fd38, 0x68 bytes, Thumb
 * func_0203fcb4 @ 0x0203fcb4, 0x84 bytes, Thumb
 * func_0203fc78 @ 0x0203fc78, 0x3a bytes, Thumb
 * func_0203fc70 @ 0x0203fc70, 0x8 bytes, Thumb
 */

typedef union {
    unsigned int w[2];
    struct {
        unsigned short f0;
        unsigned char f2, f3, f4, f5, f6, f7;
    } unk_00;
} Stamp;

typedef struct {
    unsigned char pad_00[4];
    int f4;
    unsigned char pad_08[9 - 8];
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
} Target;

typedef union {
    unsigned int word;
    unsigned char bytes[4];
} Packed;

typedef struct {
    Packed packed;
    Stamp s2;
} Combined;

extern void *func_0203fda0(void *self, Stamp *param2);
extern int func_0209e350(Stamp *a, Stamp *b);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_0203fae4(void);
extern int func_0203fec4(void *out, const void *in, int param);
extern const unsigned char data_021c74d0[3];
extern const unsigned char data_021c74d4[4];
extern int func_02040a48(int);

int func_0203fd38(void *self, Stamp *param1, Stamp *param2)
{
    int result;
    Target *target;

    result = 0;
    target = (Target *) func_0203fda0(self, param2);
    if (target != 0) {
        Combined c;
        c.packed.word = 0;
        c.packed.bytes[3] = param1->unk_00.f4;
        c.packed.bytes[2] = param1->unk_00.f3;
        c.packed.bytes[1] = param1->unk_00.f2;
        if ((unsigned int) target->f4 <= c.packed.word) {
            int cmp;

            c.s2.w[0] = 0;
            c.s2.w[1] = 0;
            c.s2.w[0] = 0;
            c.s2.w[1] = 0;
            c.s2.unk_00.f5 = param1->unk_00.f5;
            c.s2.unk_00.f4 = target->unk_0B;
            c.s2.unk_00.f3 = target->unk_0A;
            c.s2.unk_00.f2 = target->unk_09;

            cmp = func_0209e350(param1, &c.s2);
            if (cmp > 0) {
                if (cmp <= 5) {
                    result = 3;
                } else {
                    result = 2;
                }
            }
        } else {
            result = 1;
        }
    }
    return result;
}

int func_0203fcb4(void *out, const unsigned char *src, int flag)
{
    unsigned char buf0[8];
    unsigned char buf1[8];
    unsigned char buf2[8];
    unsigned char buf3[0x58];
    int ret = 0;

    if (src[5] == data_021c74d0[2] && src[4] == data_021c74d0[1] && src[3] == data_021c74d0[0]) {
        if (flag == 0 && func_0203fae4() != 0) {
            // empty
        } else {
            MI_CpuCopy8(src, buf0, 8);
            ret = func_0203fd38(out, (Stamp *) buf0, (Stamp *) data_021c74d4);
        }
    } else {
        MI_CpuCopy8(src, buf1, 8);
        func_0203fec4(buf3, buf1, 0);
        MI_CpuCopy8(src, buf2, 8);
        ret = func_0203fd38(out, (Stamp *) buf2, (Stamp *) buf3);
    }
    return ret;
}

int func_0203fc78(int arg0, void *arg1, int arg2)
{
    int ret = 0;
    if (func_02040a48(arg0) == 0) {
        char buf[8];
        MI_CpuCopy8((const void *) arg1, buf, 8);
        ret = func_0203fcb4((void *) arg0, (const unsigned char *) buf, arg2);
        if (ret == 1) {
            ret = 0;
        }
    }
    return ret;
}

int func_0203fc70(void)
{
    return (int) ((int *) data_021c74d4);
}
