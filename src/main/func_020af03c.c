/* func_020af03c @ 0x020af03c, 0x250 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x52];
    unsigned char unk_52;
    unsigned char unk_53;
    unsigned char unk_54;
    unsigned char unk_55;
} UnkStruct_020af03c;

typedef struct {
    unsigned short id;
    unsigned short unk_02;
    int unk_04;
    int unk_08;
} UnkStruct_020af03c_2;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern int func_02063cd4(void *p, int n);
extern int func_0209f150(unsigned int *p, unsigned int bit);
extern void func_0209f100(unsigned int *p, unsigned int bit);
extern void func_0209f128(unsigned int *p, unsigned int bit);
extern void func_0209df64(void *out);
extern int func_0209dcdc(void *a, void *b);
extern int func_0209de88(int y, int m, int d);
extern void func_0209e29c(void *p, int n);
extern int func_0203fea0(void *arr, void *key);
extern int func_020af28c(int v);
extern int func_0209e3ac(void *a, void *b, int mode);
extern void func_0209e140(void *p, int n);
extern void func_020afd9c(int a, int b);

extern unsigned char data_021f4a80[];
extern unsigned int data_021dc7a8[];

void func_020af03c(UnkStruct_020af03c *self, void *src)
{
    unsigned int a[2];
    unsigned char today[4];
    unsigned int c[2];
    unsigned int d[2];
    unsigned int e[2];
    unsigned int k[2];
    unsigned int k2[2];
    unsigned int f[2];
    unsigned int h[2];
    UnkStruct_020af03c_2 g1[7];
    UnkStruct_020af03c_2 g2[7];
    int v0;
    int d5;
    int e5;
    int cnt1;
    int cnt2;
    int d4;
    int d3;
    int e4;
    int e3;
    int x;
    int diff;
    int i;
    int n7;
    int n6;

    MI_CpuCopy8(src, a, 8);
    v0 = func_02063cd4(data_021f4a80, 2);
    if (func_0209f150(data_021dc7a8, 5) != 0) {
        func_0209df64(today);
        x = func_0209dcdc(today, &self->unk_52);
        if (x >= 1) {
            func_0209f100(data_021dc7a8, 5);
        } else if (x <= -7) {
            func_0209f100(data_021dc7a8, 5);
        }
    }
    if (func_0209f150(data_021dc7a8, 5) == 0) {
        MI_CpuCopy8(src, c, 8);
        x = func_0209de88(((unsigned char *) c)[5], ((unsigned char *) c)[4], ((unsigned char *) c)[3]);
        if (x == 6) {
            goto done;
        }
        if (x == 0) {
            goto done;
        }
        diff = 6 - x;
        if (diff < 0) {
            diff = -diff;
        }
        MI_CpuCopy8(c, d, 8);
        MI_CpuCopy8(c, e, 8);
        func_0209e29c(d, diff);
        func_0209e29c(e, diff + 1);
        d4 = ((unsigned char *) d)[4];
        d3 = ((unsigned char *) d)[3];
        d5 = ((unsigned char *) d)[5];
        e4 = ((unsigned char *) e)[4];
        e3 = ((unsigned char *) e)[3];
        e5 = ((unsigned char *) e)[5];
        MI_CpuCopy8(d, f, 8);
        cnt1 = func_0203fea0(g1, f);
        MI_CpuCopy8(e, h, 8);
        cnt2 = func_0203fea0(g2, h);
        i = n6 = n7 = 0;
        for (; i < cnt1; i++) {
            if (func_020af28c(g1[i].id) != 0) {
                n7++;
            }
        }
        for (i = 0; i < cnt2; i++) {
            if (func_020af28c(g2[i].id) != 0) {
                n6++;
            }
        }
        if (n7 != 0) {
            goto done;
        }
        if (n6 != 0) {
            goto done;
        }
        if (v0 == 0) {
            self->unk_54 = (unsigned char) d5;
            self->unk_53 = (unsigned char) d4;
            self->unk_52 = (unsigned char) d3;
            self->unk_55 = 0;
        } else {
            self->unk_54 = (unsigned char) e5;
            self->unk_53 = (unsigned char) e4;
            self->unk_52 = (unsigned char) e3;
            self->unk_55 = 0;
        }
        func_0209f100(data_021dc7a8, 6);
        func_0209f128(data_021dc7a8, 5);
    }
done:
    if (func_0209f150(data_021dc7a8, 5) != 0) {
        k[0] = 0;
        k[1] = 0;
        ((unsigned char *) k)[5] = self->unk_54;
        ((unsigned char *) k)[4] = self->unk_53;
        ((unsigned char *) k)[3] = self->unk_52;
        ((unsigned char *) k)[2] = 6;
        ((unsigned char *) k)[1] = 0;
        if (func_0209e3ac(k, a, 0x38) == -1) {
            func_0209f100(data_021dc7a8, 5);
        } else {
            MI_CpuCopy8(k, k2, 8);
            func_0209e140(k2, 4);
            if (func_0209e3ac(k2, a, 0x38) == -1) {
                if (func_0209e3ac(a, k, 0x38) == -1) {
                    if (func_0209f150(data_021dc7a8, 6) == 0) {
                        func_020afd9c(self->unk_53, self->unk_52);
                        func_0209f128(data_021dc7a8, 6);
                    }
                }
            }
        }
    }
}
