/* func_02066abc @ 0x02066abc, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[8];
    int unk_14;
    unsigned char unk_18;
    unsigned char pad_19[0x13e8 - 0x19];
    int unk_13E8;
    unsigned char pad_13EC[0x1e77 - 0x13ec];
    unsigned char unk_1E77;
} UnkStruct_02066abc;

extern unsigned char data_021f43f8;
extern unsigned char data_021f43e8;

extern void func_02068388(void *obj, int cond);
extern void func_02067218(void *obj);
extern void func_02067c04(void *obj);
extern void func_02067be0(void *obj);
extern void func_02067bb8(void *obj);
extern void func_02067b54(void *obj);
extern void func_02067b3c(void *obj);
extern void func_02067b1c(void *obj);

void func_02066abc(UnkStruct_02066abc *self)
{
    int st = self->unk_13E8;
    int isA, isB, isC;
    int newA, newB, act, reset;
    // 8 bytes of frame that are never used; a pointer to a volatile object keeps the slot.
    volatile int dbg[2];
    volatile int *dp = dbg;

    if (st == 2) {
        isA = 1;
    } else {
        isA = 0;
    }
    if (st == 4) {
        isB = 1;
    } else {
        isB = 0;
    }
    if (st == 5) {
        isC = 1;
    } else {
        isC = 0;
    }

    newA = 6;
    newB = 6;
    reset = 0;
    act = reset;

    if (self->unk_18 != 0) {
        self->unk_18 = 0;
        func_02068388(self, 0);
    } else if (isA != 0 || isB != 0 || isC != 0) {
        newA = 1;
        newB = 3;
        if (isC != 0) {
            act = 1;
        } else if (isB != 0) {
            act = 2;
        } else {
            act = 3;
        }
    } else {
        unsigned char g1 = data_021f43f8;
        unsigned char v = self->unk_1E77;
        unsigned char g2 = data_021f43e8;
        if (v == g2) {
            newA = 0;
            newB = 4;
            act = 6;
        } else if (self->unk_14 != 4) {
            newA = 0;
            newB = 4;
            act = 5;
        } else if (v != g1) {
            reset = 1;
            act = 4;
        }
    }

    if (reset != 0) {
        func_02067218(self);
        newA = 1;
        newB = 3;
    }
    if (newA != 6) {
        self->unk_13E8 = newA;
    }
    if (newB != 6) {
        self->unk_08 = newB;
        if (act == 1) {
            func_02067c04(self);
        } else if (act == 2) {
            func_02067be0(self);
        } else if (act == 3) {
            func_02067bb8(self);
        } else if (act == 4) {
            func_02067b54(self);
        } else if (act == 5) {
            func_02067b3c(self);
        } else if (act == 6) {
            func_02067b1c(self);
        }
    }
}
