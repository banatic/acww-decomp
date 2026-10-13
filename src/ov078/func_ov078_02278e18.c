/* func_ov078_02278e18 @ 0x02278e18, 0x15c bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278e18_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278e18_2;

typedef struct UnkStruct_02278e18_3 {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02278e18_3;

typedef struct UnkStruct_02278e18 {
    int w[9];
} UnkStruct_02278e18;

extern int data_ov078_02279bd8;

extern void func_020984e8(void);
extern void func_02099640(void);
extern void *func_0209a850(void);
extern void func_02094fd4(UnkStruct_02278e18 *t);
extern void func_02094fbc(UnkStruct_02278e18 *t);
extern int func_02099e9c(unsigned short *p);
extern void *func_0209b0f0(void *p);
extern int func_0209bd44(void *p);
extern int func_0209bba0(void *p);
extern void func_0209bb90(void *p, int a);
extern int func_0202ea80(int a, int b);
extern int func_0209b0c4(void *p, UnkStruct_02278e18 *t);
extern void func_02068404(int a, int b, UnkStruct_02278e18 *t);
extern int func_02099fe8(void);
extern int func_0209b044(void *p);

void func_ov078_02278e18(UnkStruct_02278e18_2 *self, UnkStruct_02278e18_3 *out)
{
    unsigned short id;
    UnkStruct_02278e18 tmp;
    void *obj;

    func_020984e8();
    func_02099640();
    obj = func_0209a850();
    func_02094fd4(&tmp);
    out->unk_00 = (int) &data_ov078_02279bd8;
    if (self->unk_B4 == -1) {
        id = 0x13ac;
        self->unk_B4 = func_02099e9c(&id);
    }
    if (self->unk_B4 >= 0) {
        out->unk_04 = 0x14;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209bd44(func_0209b0f0(obj)) != 0) {
        if (func_0209bba0(func_0209b0f0(obj)) == 3) {
            out->unk_04 = 0;
            func_02094fbc(&tmp);
            return;
        }
    }
    if (func_0202ea80(0xb, 1) == 0) {
        out->unk_04 = 1;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209bd44(func_0209b0f0(obj)) == 0) {
        out->unk_04 = 4;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209bd44(func_0209b0f0(obj)) != 0) {
        if (func_0209bba0(func_0209b0f0(obj)) == 0) {
            if (func_0209b0c4(obj, &tmp) != 0) {
                func_02068404(self->unk_40, 0, &tmp);
            }
            out->unk_04 = 9;
            func_02094fbc(&tmp);
            return;
        }
    }
    if (func_02099fe8() < 0) {
        out->unk_04 = 0x12;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209b044(obj) != 0) {
        if (func_0209b0c4(obj, &tmp) != 0) {
            func_02068404(self->unk_40, 0, &tmp);
        }
        out->unk_04 = 0xa;
    } else if (func_0209bba0(func_0209b0f0(obj)) == 1) {
        func_0209bb90(func_0209b0f0(obj), 2);
        out->unk_04 = 0xc;
    }
    func_02094fbc(&tmp);
}
