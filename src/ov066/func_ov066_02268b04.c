/* func_ov066_02268b04 @ 0x02268b04, 0xe0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Pkt {
    u16 unk_00;
    u16 err; // 0x02
    unsigned char pad_04[4];
    u16 kind; // 0x08
} Pkt;

typedef struct UnkStruct_02268b04 {
    unsigned char pad_00[0xc0];
    u32 b0 : 2;   // 0xc0, bits 0..1
    int flag : 1; // bit 2
    u32 rest : 29;
} UnkStruct_02268b04;

extern UnkStruct_02268b04 *data_ov066_0226bdf4;
int func_ov066_02266e08(void);
void func_ov066_0226686c(u16 err);
extern void func_ov066_02269154(void *p);
void func_ov066_0226908c(Pkt *p);
void func_ov066_02266e64(void);
void func_ov066_02268f98(Pkt *p);

void func_ov066_02268b04(Pkt *p)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (p->err == 0) {
        switch (p->kind) {
            case 0:
                break;
            case 2:
                func_ov066_02269154(p);
                break;
            case 7:
                func_ov066_0226908c(p);
                break;
            case 9:
                if (data_ov066_0226bdf4->flag) {
                    func_ov066_02266e64();
                } else {
                    func_ov066_02268f98(p);
                }
                break;
        }
    } else {
        func_ov066_0226686c(p->err);
    }
}
