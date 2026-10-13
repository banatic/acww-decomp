/* func_ov142_0229a0f8 @ 0x0229a0f8, 0x104 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov142_0229abfc(void *self);
extern void func_ov142_02299648(void *self, int val);
extern int func_ov142_02299668(void *self, int val);
extern void func_ov142_02299658(void *self, int val);
extern unsigned short *func_ov142_0229a644(void *self, int val);
extern int func_0204c260(void *local);
extern int func_0204c7f0(void *local);
extern void func_ov142_0229ac38(void *self);
extern void func_ov142_0229ac9c(void *self, int val);
extern int func_ov004_0223d03c(void);
extern void func_ov004_0223d064(void);
extern void func_ov004_0223d08c(int a, void *arg);
extern unsigned char data_020e54a8;

typedef struct {
    unsigned char pad_00[0xb8];
    short unk_B8;
    unsigned char pad_BA[4];
    unsigned char unk_BE;
    unsigned char unk_BF;
} UnkStruct_0229a0f8;

int func_ov142_0229a0f8(UnkStruct_0229a0f8 *self, int param1, int param2)
{
    int result = 1;
    if (self->unk_BE == param1 && self->unk_B8 == param2) {
        result = 0;
    }
    self->unk_BE = param1;
    self->unk_B8 = param2;

    if (param2 == -1) {
        func_ov142_0229abfc(self);
        func_ov142_02299648(self, 0x20);
        self->unk_BF = 6;
        {
            unsigned int flag = (data_020e54a8 == 1);
            if (flag > 0) {
                if (func_ov142_02299668(self, 0x40) != 0) {
                    func_ov142_02299648(self, 0x40);
                    func_ov004_0223d03c();
                    func_ov004_0223d064();
                }
            }
        }
    } else {
        unsigned short val;
        volatile unsigned short local;
        val = *func_ov142_0229a644(self, param2);
        local = 0xfff1;
        local = val;
        if (func_0204c260((void *) &local) != 0) {
            func_ov142_0229ac38(self);
            self->unk_BF = 6;
            func_ov142_02299648(self, 0x20);
        } else {
            int ret = func_0204c7f0((void *) &local);
            func_ov142_0229ac9c(self, ret);
            func_ov142_02299658(self, 0x20);
            self->unk_BF = 5;
        }
        {
            unsigned int flag = (data_020e54a8 == 1);
            if (flag > 0) {
                func_ov142_02299658(self, 0x40);
                func_ov004_0223d08c(func_ov004_0223d03c(), (void *) &local);
            }
        }
    }
    func_ov142_02299658(self, 2);
    return result;
}
