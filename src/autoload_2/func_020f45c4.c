/* func_020f45c4 @ 0x020f45c4, 0x84 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
    struct UnkStruct_020f45c4 *unk_30;
    char pad_34[0x4d - 0x34];
    u8 unk_4D;
} UnkStruct_020f45c4_2;
typedef struct UnkStruct_020f45c4 {
    char pad_00[0x3c];
    u8 unk_3C;
} UnkStruct_020f45c4;
typedef struct {
    void *vtable;
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
} UnkStruct_020f45c4_3;
extern UnkStruct_020f45c4_2 data_021fd1bc;
extern void func_020f65bc(UnkStruct_020f45c4 *ptr, int param);
extern void func_020f11d0(UnkStruct_020f45c4_2 *global, int a, int b);
extern void NNS_SndPlayerSetPlayerVolume(int a, int b);
extern void func_020f5a3c(char value);
extern unsigned char data_0213efb4[];

UnkStruct_020f45c4_3 *func_020f45c4(UnkStruct_020f45c4_3 *this)
{
    UnkStruct_020f45c4 *p;
    this->vtable = (void *) data_0213efb4;
    data_021fd1bc.unk_2C = this;
    data_021fd1bc.unk_4D = 0;
    data_021fd1bc.unk_30->unk_3C = 0;
    if (data_021fd1bc.unk_30 != 0) {
        func_020f65bc(data_021fd1bc.unk_30, 0xd2);
    }
    func_020f11d0(&data_021fd1bc, 0x7f, 0x7f);
    NNS_SndPlayerSetPlayerVolume(0xf, 0x64);
    this->unk_04 = -1;
    this->unk_05 = 0;
    this->unk_06 = 0;
    func_020f5a3c(0);
    return this;
}
