/* func_ov066_0226a074 @ 0x0226a074, 0xec bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Pkt {
    u16 unk_00;
    u16 err; // 0x02
    unsigned char pad_04[4];
    u16 id;  // 0x08
    u16 seq; // 0x0a
} Pkt;

typedef struct Ctl {
    unsigned char pad_00[4];
    int state; // 0x04
    u8 unk_08; // 0x08
} Ctl;

typedef struct UnkStruct_0226a074 {
    unsigned char pad_00[0xc0];
    u32 lo7 : 7; // 0xc0 bits 0..6
    int b7 : 1;  // bit 7
    u32 hi : 24;
} UnkStruct_0226a074;

extern u16 data_ov066_0226be04;
extern u8 data_ov066_0226bdfc;
extern u16 data_ov066_0226be00;
extern Ctl *data_ov066_0226bdec;
extern UnkStruct_0226a074 *data_ov066_0226bdf4;
int func_ov066_02269f6c(u16 id);
void func_ov066_0226686c(u16 err);
void func_ov066_02266bf4(void);

void func_ov066_0226a074(Pkt *p)
{
    u16 seq;
    u16 id;
    if (p->err == 0) {
        seq = p->seq;
        id = p->id;
        if (data_ov066_0226be04 > seq) {
            data_ov066_0226be04 = seq;
            data_ov066_0226be00 = (u16) (1 << (id - 1));
            data_ov066_0226bdfc = 1;
        } else if (data_ov066_0226be04 == seq) {
            data_ov066_0226be00 = (u16) (data_ov066_0226be00 | (1 << (id - 1)));
            data_ov066_0226bdfc = (u8) (data_ov066_0226bdfc + 1);
        }
        if (func_ov066_02269f6c(id) != 0) {
            data_ov066_0226bdec->state = 4;
            if (data_ov066_0226bdec->unk_08 == 0xfe) {
                data_ov066_0226bdf4->b7 = 0;
            }
            func_ov066_02266bf4();
        }
    } else {
        func_ov066_0226686c(p->err);
    }
}
