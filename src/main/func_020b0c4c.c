/* func_020b0c4c @ 0x020b0c4c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b6788(void);
extern void func_02073dd4(void *a, int b);
extern int func_020b0d08(void *a, unsigned int idx, int flag, int *b, int *c, int *d);
extern void func_020952ac(int idx, int *a, int *b, int val);
extern int func_020961c0(void);
extern void func_020961f0(int a, int b);
extern void func_0202f134(int a, int b, int c, int d);

typedef struct {
    unsigned char pad_00[4];
    void *target;
} self_t;

typedef struct {
    int arrA[2];
    int valA;
    int arrB[1];
    unsigned char pad_10[4];
    int valB;
    int arrC[3];
    int arrD[1];
    unsigned char pad_end[8];
} LocalData;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020b0c4c;

extern UnkStruct_020b0c4c *data_020ccf94;
extern int data_021f42f4;

int func_020b0c4c(self_t *self)
{
    LocalData data;
    void *target = self->target;
    unsigned int idx;

    if (target != 0) {
        if (func_020b65c4() != 0xd && func_020b65c4() != 0xe && func_020b65c4() != 0x2f) {
            if (func_020b6788() != 0) {
                func_02073dd4(data_020ccf94, data_020ccf94->unk_64);
                for (idx = 0; idx < 4; idx++) {
                    if (func_020b0d08(target, idx, 1, data.arrC, data.arrA, &data.valA) != 0) {
                        func_020952ac(idx, data.arrC, data.arrA, data.valA);
                    }
                }
            } else {
                for (idx = 0; idx < 4; idx++) {
                    if (func_020b0d08(target, idx, 0, data.arrD, data.arrB, &data.valB) != 0) {
                        func_020961f0(idx, func_020961c0());
                        func_020952ac(idx, data.arrD, data.arrB, data.valB);
                    }
                }
            }
        }
    }

    func_0202f134(0xb, data_021f42f4, 0, 0);
    return 1;
}
