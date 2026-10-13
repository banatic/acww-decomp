/* func_020a958c @ 0x020a958c, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 unk_44;
    u8 pad_45[0x48];
    u8 unk_8D;
    u8 pad_8E[2];
    u8 unk_90;
    u8 pad_91[0xb];
    u32 unk_9C;
    u32 unk_A0;
} UnkStruct_020a958c;
typedef struct {
    u32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 pad[2];
} Elem;
typedef struct {
    u8 pad[8];
    u16 val;
} GUnknown1;
typedef struct {
    u8 pad[4];
    u32 val;
} GUnknown2;
extern void func_02064658(void *dest, void *src, unsigned int size, unsigned int offset);
extern unsigned int func_020a9ae4(void *p);
extern unsigned char func_020a9adc(void *p);
extern void MI_CpuCopy8(void *p, void *q, unsigned int size);
extern unsigned char data_021f4428[];

extern unsigned char data_021f4458[];

int func_020a958c(UnkStruct_020a958c *self)
{
    UnkStruct_020a958c *p = self;
    unsigned char idx;
    int off;
    int val2;
    unsigned int flag;
    unsigned int size;
    Elem arr[2];
    GUnknown2 *ptr;
    int count;
    int i;
    idx = p->unk_8D;
    off = (idx * 0xc) + 0x10;
    val2 = (unsigned int) data_021f4458;
    flag = ((((GUnknown1 *) val2)->val - 1) == idx) ? (1u) : (0u);
    size = (flag) ? (0xc) : (0x18);
    func_02064658(&p->unk_44, arr, size, off + 0x20);
    count = (flag) ? (1) : (2);
    for (i = 0; i < count; i++) {
        arr[i].unk_00 = func_020a9ae4(&arr[i]);
        arr[i].unk_04 = func_020a9adc(&arr[i].unk_04);
        arr[i].unk_05 = func_020a9adc(&arr[i].unk_05);
        arr[i].unk_06 = func_020a9adc(&arr[i].unk_06);
        arr[i].unk_07 = func_020a9adc(&arr[i].unk_07);
        arr[i].unk_08 = func_020a9adc(&arr[i].unk_08);
        arr[i].unk_09 = func_020a9adc(&arr[i].unk_09);
    }

    p->unk_9C = arr[0].unk_00;
    if (flag) {
        ptr = (GUnknown2 *) data_021f4428;
        p->unk_A0 = ptr->val - (p->unk_9C + 8);
    } else {
        p->unk_A0 = arr[1].unk_00 - p->unk_9C;
    }
    MI_CpuCopy8(arr, &p->unk_90, 0xc);
    return 1;
}
