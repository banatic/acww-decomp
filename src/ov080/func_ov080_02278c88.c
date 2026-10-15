/* func_ov080_02278c88 @ 0x02278c88, 0x164 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_02099020(void *handle, int kind);
extern void func_02098ff8(void *handle, int kind);
extern int func_020644cc(int val);
extern int func_02099e9c(unsigned short *ptr);
extern int func_0203cc38(void);
extern int func_02099fe8(void);
extern void *func_02098844(void *table, int index);
extern int func_02099a28(unsigned int object);
extern int func_0203cc1c(void);

extern char data_ov080_022793a8;
extern char data_ov080_02279398;
extern char data_ov080_022793bc;
extern char data_021dc7bc;

typedef struct {
    void *ptr;
    unsigned char status;
} OutputType;

typedef struct {
    unsigned char pad_00[0xb4];
    int unk_B4;
} InputType;

void func_ov080_02278c88(InputType *self, OutputType *out)
{
    void *handle;
    int i;

    handle = func_020984e8();

    if (func_02099020(handle, 1) != 0) {
        out->ptr = &data_ov080_022793a8;
        if (func_02099020(handle, 0xd) == 0) {
            out->status = 0;
            func_02098ff8(handle, 0xd);
        } else {
            out->status = (unsigned char) (func_020644cc(4) + 3);
        }
        func_02098ff8(handle, 0xa);
        return;
    }

    if (self->unk_B4 == -1) {
        unsigned short val = 0x37e0;
        self->unk_B4 = func_02099e9c(&val);
        if (self->unk_B4 < 0) {
            // fall through
        } else {
            out->ptr = &data_ov080_02279398;
            out->status = 0;
            return;
        }
    }

    out->ptr = &data_ov080_022793bc;

    if (func_02099020(handle, 0x21) == 0) {
        if (func_0203cc38() != 0) {
            out->status = 0;
            if (func_02099fe8() < 0) {
                out->status = 9;
                return;
            } else {
                for (i = 0; i < 4; i++) {
                    void *p = func_02098844(&data_021dc7bc, i);
                    if (p != 0 && func_02099a28((unsigned int) p) != 0 && p != handle && func_02099020(p, 0x21) != 0) {
                        out->status = 2;
                        return;
                    }
                }
                return;
            }
        }
    }

    if (func_02099020(handle, 0x22) == 0) {
        if (func_0203cc1c() != 0) {
            out->status = 3;
            if (func_02099fe8() < 0) {
                out->status = 0xa;
                return;
            } else {
                for (i = 0; i < 4; i++) {
                    void *p = func_02098844(&data_021dc7bc, i);
                    if (p != 0 && func_02099a28((unsigned int) p) != 0 && p != handle && func_02099020(p, 0x22) != 0) {
                        out->status = 5;
                        return;
                    }
                }
                return;
            }
        }
    }

    out->status = (unsigned char) (func_020644cc(3) + 6);
}
