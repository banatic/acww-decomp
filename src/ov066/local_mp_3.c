/* local_mp_3: 2 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02268f1c @ 0x02268f1c, 0x7c bytes, ARM
 * func_ov066_02268ed4 @ 0x02268ed4, 0x48 bytes, ARM
 */

typedef struct {
    unsigned char pad_00[0x0c];
    unsigned int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
} UnkStruct_02268f1c;

struct UnkStruct_02268ed4 {
    char pad_00[0x98];
    unsigned short flags;
};

extern void MI_CpuCopy8(unsigned int, void *, int);
extern struct UnkStruct_02268ed4 *data_ov066_0226bdf4;
extern void func_ov066_0226943c(void);

void func_ov066_02268ed4(int bit, void *ptr);

void func_ov066_02268f1c(UnkStruct_02268f1c *s)
{
    unsigned short v;
    if (s->unk_10 == 0) {
        return;
    }
    MI_CpuCopy8(s->unk_0C, &v, 4);
    if (v == 0) {
        return;
    }
    if (v == 1) {
        return;
    }
    if (v != 2) {
        return;
    }
    func_ov066_02268ed4((unsigned short) s->unk_12, (void *) s->unk_0C);
    return;
}

void func_ov066_02268ed4(int bit, void *ptr)
{
    unsigned char local[8];
    MI_CpuCopy8((unsigned int) ptr, local, 8);
    data_ov066_0226bdf4->flags |= (1 << bit);
    func_ov066_0226943c();
}
