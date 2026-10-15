/* func_ov003_022115a4 @ 0x022115a4, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Status {
    unsigned char flag;
    unsigned short val;
} Status;

typedef struct Vec {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Vec;

typedef struct UnkStruct_022115a4 {
    unsigned char pad_00[0x7f0];
    unsigned int flag;
    unsigned char pad_7F4[0x100 - 4];
    unsigned char data;
} UnkStruct_022115a4;

extern void func_ov003_022118b8(unsigned char *data, unsigned int *out, unsigned short *val, unsigned char *flag);
extern void func_0204f794(Vec *vec, unsigned int a, unsigned int b);
extern int func_ov003_022118f8(UnkStruct_022115a4 *self, Vec *vec, unsigned short val, unsigned char flag, int c, int d);

void func_ov003_022115a4(UnkStruct_022115a4 *self, int arg2)
{
    Status status;
    unsigned int out[2];
    Vec vec;
    Vec outVec;

    if (self->flag != 0) {
        return;
    }
    out[0] = 0;
    out[1] = 0;
    func_ov003_022118b8(&self->data, out, &status.val, &status.flag);
    func_0204f794(&vec, out[0], out[1]);
    outVec.x = vec.x;
    outVec.y = vec.y;
    outVec.z = vec.z;
    func_ov003_022118f8(self, &outVec, status.val, status.flag, 6, arg2);
}
