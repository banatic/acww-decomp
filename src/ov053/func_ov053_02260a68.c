/* func_ov053_02260a68 @ 0x02260a68, 0x140 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_ov053_02260ba8(void *self);
extern int func_ov053_0226075c(void *self);
extern int func_ov053_02260474(int);
extern void func_ov053_02260bb0(void *self, int);
extern int func_0202ea80(int, int);
extern int func_02099020(int, int);
extern void func_02098ff8(int, int);
extern int func_020644cc(int);

extern unsigned int data_ov053_02261c60;
extern void *data_ov053_02261980;

typedef struct Entry {
    void *ptr;
    unsigned char flag;
} Entry;

extern Entry data_ov053_02261a90[14];

typedef struct UnkStruct_02260a68 {
    unsigned char pad_00[0xb0];
    int idx;
    int kind;
} UnkStruct_02260a68;

typedef struct UnkStruct_02260a68_2 {
    void *ptr;
    unsigned char flag;
} UnkStruct_02260a68_2;

void func_ov053_02260a68(UnkStruct_02260a68 *self, UnkStruct_02260a68_2 *out)
{
    int v;
    unsigned int guard;
    void *p;

    v = func_020984e8();

    guard = data_ov053_02261c60;
    if ((guard & 1) == 0) {
        p = data_ov053_02261980;
        data_ov053_02261a90[0].ptr = p;
        data_ov053_02261a90[1].ptr = p;
        data_ov053_02261a90[2].ptr = p;
        data_ov053_02261a90[3].ptr = p;
        data_ov053_02261a90[4].ptr = p;
        data_ov053_02261a90[5].ptr = p;
        data_ov053_02261a90[6].ptr = p;
        data_ov053_02261a90[7].ptr = p;
        data_ov053_02261a90[8].ptr = p;
        data_ov053_02261a90[9].ptr = p;
        data_ov053_02261a90[10].ptr = p;
        data_ov053_02261a90[11].ptr = p;
        data_ov053_02261a90[12].ptr = p;
        data_ov053_02261a90[13].ptr = p;
        data_ov053_02261c60 = guard | 1;
    }

    if (func_ov053_02260ba8(self) == 4) {
        out->ptr = data_ov053_02261a90[self->idx].ptr;
        out->flag = (unsigned char) func_ov053_0226075c(self);
    } else {
        if (func_ov053_02260ba8(self) != 0 && func_ov053_02260ba8(self) != 3 && func_ov053_02260ba8(self) != 5 &&
            func_ov053_02260ba8(self) != 7 && func_ov053_02260ba8(self) != 8 && func_ov053_02260ba8(self) != 9 &&
            func_ov053_02260ba8(self) != 0xa) {
            if (func_ov053_02260474(self->kind) == 0) {
                if (func_0202ea80(0x13, 0) == 0) {
                    if (func_02099020(v, 0xb) == 0) {
                        func_ov053_02260bb0(self, 1);
                        func_02098ff8(v, 0xb);
                    } else {
                        func_ov053_02260bb0(self, 2);
                    }
                } else {
                    func_ov053_02260bb0(self, func_020644cc(3) + 0xb);
                }
            } else {
                func_ov053_02260bb0(self, 6);
            }
        }
        if (self->idx >= 0 && self->idx < 0xe) {
            out->flag = data_ov053_02261a90[self->idx].flag;
            out->ptr = data_ov053_02261a90[self->idx].ptr;
        }
    }
}
