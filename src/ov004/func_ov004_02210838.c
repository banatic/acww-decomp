/* func_ov004_02210838 @ 0x02210838, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_02210838;

extern UnkStruct_02210838 data_ov004_02256dc8;
extern int data_ov004_02256c68;
extern int data_ov004_02256dbc;
extern short FX_SinCosTable_[];
extern void __register_global_object(UnkStruct_02210838 *a, void *destructor, void *c);
extern void func_020012dc(void *arg0);
extern void *func_020961a8(int i);

UnkStruct_02210838 *func_ov004_02210838(char *self)
{
    void *p;
    int i;

    if ((data_ov004_02256c68 & 1) == 0) {
        __register_global_object(&data_ov004_02256dc8, ((void *) &func_020012dc), &data_ov004_02256dbc);
        data_ov004_02256c68 |= 1;
    }
    data_ov004_02256dc8.unk_00 = *(int *) (self + 0x5c);
    data_ov004_02256dc8.unk_04 = *(int *) (self + 0x60);
    data_ov004_02256dc8.unk_08 = *(int *) (self + 0x64);
    p = func_020961a8(4);
    if (p != 0) {
        i = *(u16 *) ((char *) p + 0x8e) >> 4;
        data_ov004_02256dc8.unk_00 = *(int *) ((char *) p + 0x5c) + FX_SinCosTable_[i * 2];
        data_ov004_02256dc8.unk_04 = *(int *) ((char *) p + 0x60);
        data_ov004_02256dc8.unk_08 = *(int *) ((char *) p + 0x64) + FX_SinCosTable_[i * 2 + 1];
    }
    return &data_ov004_02256dc8;
}
