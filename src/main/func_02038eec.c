/* func_02038eec @ 0x02038eec, 0x178 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02038eec {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02038eec;

extern int func_020960d8(int);
extern int func_02073d90(UnkStruct_02038eec *);
extern int func_0203ec98(void);
extern void *func_0203a404(void *);
extern int func_020b4980(void *, void *, int);
extern void *func_02094fd4(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern void *func_02095074(int, void *);
extern void func_020398e8(int, void *, void *);
extern void RtcSendPxiCommand(int);
extern void *func_02094fbc(void *);
extern void *func_0203a3ec(void *);

extern u16 data_021fbe40[];
extern UnkStruct_02038eec *data_020ccf94;
extern int data_021c6730;

void func_02038eec(int argument)
{
    int f0;
    int res5;
    int v8;
    int vc;
    UnkStruct_02038eec *obj;
    u8 cmd;
    int buf1[13];
    int buf2[8];
    int r;
    int d;
    int skip;
    u16 val;
    int r7;
    int r6;
    int r4;
    int r5;
    int r2;

    r = func_020960d8(4);
    v8 = 1;
    if (r != 0x28 && r != 0x2b && r != 8 && r != 9) {
        v8 = 0;
    }

    val = data_021fbe40[1];

    if (val & 4) {
        f0 = 1;
    } else {
        f0 = 0;
    }

    if (val & 0x400) {
        r7 = 1;
    } else {
        r7 = 0;
    }

    if (val & 0x800) {
        r6 = 1;
    } else {
        r6 = 0;
    }

    if (val & 1) {
        r4 = 1;
    } else {
        r4 = 0;
    }

    if (val & 2) {
        r5 = 1;
    } else {
        r5 = 0;
    }

    vc = 1;
    if ((val & 8) == 0 && f0 == 0 && r7 == 0 && r6 == 0 && r4 == 0 && r5 == 0) {
        vc = 0;
    }

    obj = data_020ccf94;
    res5 = func_02073d90(obj);
    if (func_0203ec98() == 0) {
        d = 1;
    } else {
        d = 0;
    }

    if (data_021c6730 > 0) {
        return;
    }
    if (v8 == 0 || vc == 0 || res5 == 0 || d == 0) {
        return;
    }

    func_0203a404(buf1);

    skip = 0;
    if (f0 != 0) {
        r2 = 0xf0;
    } else if (r7 != 0) {
        r2 = 0xf1;
    } else if (r6 != 0) {
        r2 = 0xf2;
    } else if (r4 != 0) {
        r2 = 0xf3;
    } else if (r5 != 0) {
        r2 = 0xf4;
    } else {
        r2 = 0xef;
        if (obj->unk_64 != 0) {
            skip = 1;
        }
    }

    if (skip == 0) {
        cmd = (u8) r2;
        func_020b4980(buf1, &cmd, 0);
        func_02094fd4(buf2);
        func_02095074(func_02099870((int) func_020984e8()), buf2);
        func_020398e8(obj->unk_64, buf2, buf1);
        RtcSendPxiCommand(0x32);
        data_021c6730 = 0x1e;
        func_02094fbc(buf2);
    }
    func_0203a3ec(buf1);
}
