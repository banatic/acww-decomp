/* func_ov114_0229c9dc @ 0x0229c9dc, 0x74 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    int unk_08;
} UnkStruct_0229c9dc;

typedef struct {
    char pad_00[0x1000];
    UnkStruct_0229c9dc arr[9];
    char pad_106C[0x21C];
    int unk_1288;
} BigStruct;

extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern int func_02088d94(const void *arg);
extern void func_ov114_0229cb7c(BigStruct *base, int arg);
extern const unsigned char data_ov114_0229dac0[8];
extern const char data_ov114_0229db20[];

void func_ov114_0229c9dc(BigStruct *base)
{
    int i = 0;
    UnkStruct_0229c9dc *arr = base->arr;
    int neg = ~i;
    do {
        UnkStruct_0229c9dc *elem = &arr[i];
        MI_CpuCopy8(data_ov114_0229dac0, elem, 8);
        elem->unk_04 = (elem->unk_04 & 0xfffffc00u) | (((i << 1) + 0xc0) & 0x3ffu);
        elem->unk_08 = neg;
        i++;
    } while (i < 9);
    base->unk_1288 = func_02088d94(data_ov114_0229db20) + 0x70;
    func_ov114_0229cb7c(base, 0);
}
