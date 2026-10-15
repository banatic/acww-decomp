/* func_020a4f0c @ 0x020a4f0c, 0x130 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020a4f0c {
    u8 pad_00[0xac];
    void *unk_AC;
    void *unk_B0;
    void *unk_B4;
    void *unk_B8;
    void *unk_BC;
    void *unk_C0;
    void *unk_C4;
    void *unk_C8;
    void *unk_CC;
};

extern int data_021e5a2c;
extern void *data_020ccf94;
extern int data_021f3c3c;
extern int data_021f3c24;

extern int func_020b65c4(void);
extern void func_0207ac20(int *);
extern int func_02073d90(void *);
extern void func_020e993c(void *, void *);
extern void func_020a0070(int);

int func_020a4f0c(struct UnkStruct_020a4f0c *o)
{
    int condition_value0;
    if (func_020b65c4() == 6) {
        func_0207ac20(&data_021e5a2c);
    }
    if (func_02073d90(data_020ccf94) && (func_020b65c4() == 0xb || func_020b65c4() == 9)) {
        return 1;
    }
    data_021f3c3c = 0;
    if (func_020b65c4() == 0x2e || func_020b65c4() == 6 || func_020b65c4() == 9 || func_020b65c4() == 0xb) {
        func_020e993c(o->unk_AC, o->unk_B0);
        func_020e993c(o->unk_AC, o->unk_B4);
        func_020e993c(o->unk_AC, o->unk_C4);
    }
    if (func_020b65c4() == 9) {
        func_020e993c(o->unk_AC, o->unk_BC);
    }
    if (data_021f3c24) {
        func_020e993c(o->unk_AC, (void *) data_021f3c24);
        data_021f3c24 = 0;
    }
    if ((condition_value0 = (int) (o->unk_CC))) {
        func_020a0070(condition_value0);
        func_020e993c(o->unk_AC, o->unk_CC);
        o->unk_CC = 0;
    }
    if (o->unk_C8) {
        func_020e993c(o->unk_AC, o->unk_C8);
    }
    if (func_020b65c4() == 0x2e) {
        func_020e993c(o->unk_AC, o->unk_B8);
        func_020e993c(o->unk_AC, o->unk_C0);
    }
    return 1;
}
