/* xct_exchange_2: 4 functions, module ov055
 * mwccarm 1.2/base -O4,s
 * func_ov055_0226068c @ 0x0226068c, 0x68 bytes, Thumb
 * func_ov055_02260668 @ 0x02260668, 0x24 bytes, Thumb
 * func_ov055_0226063c @ 0x0226063c, 0x2c bytes, Thumb
 * func_ov055_02260610 @ 0x02260610, 0x2c bytes, Thumb
 */

struct UnkStruct_02260668 {
    char pad_00[0x714];
    char unk_714[0x950];
};

extern void func_0209010c(void *);
extern void func_02090140(void *, int);
extern void *func_02090040(int);
extern void MI_CpuCopy8(void *, const void *, int);
extern unsigned char data_021f37f4[];
extern int func_02014868(void *);
extern int func_0201c014(void *);

void func_ov055_02260668(struct UnkStruct_02260668 *p);

void func_ov055_0226068c(void *p)
{
    void *r4;
    unsigned char b;

    r4 = func_02090040(4);
    b = ((unsigned char *) p)[0x1bc0];
    if (b == 2) {
        MI_CpuCopy8((void *) ((char *) p + 0x1abc), (const void *) data_021f37f4, 0x104);
        func_ov055_02260668((struct UnkStruct_02260668 *) p);
    } else if (b == 1) {
        MI_CpuCopy8((void *) ((char *) p + 0x116c), r4, 0x950);
        func_0209010c(r4);
        func_02090140(r4, 1);
    }
}

void func_ov055_02260668(struct UnkStruct_02260668 *p)
{
    MI_CpuCopy8((void *) p->unk_714, (const void *) (func_02090040(4)), 0x950);
}

int func_ov055_0226063c(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

int func_ov055_02260610(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
