/* func_ov095_0229c084 @ 0x0229c084, 0x80 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229b3ec(void *obj);
extern void func_ov095_022999a8(void *obj, int a);
extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_020950c0(void *argument0);
extern void func_0200458c(int arg);

extern int data_ov095_0229e6b4;
extern int data_ov095_0229e6e4;

struct UnkStruct_0229c084 {
    unsigned char pad_00[0x14];
    unsigned short unk_14;
    unsigned char unk_16;
    unsigned char unk_17;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char pad_1C[0x20 - 0x1c];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    unsigned char pad_34[0x42 - 0x34];
    unsigned char unk_42;
    unsigned char pad_43[0x44 - 0x43];
    void *unk_44;
};

void func_ov095_0229c084(struct UnkStruct_0229c084 *obj, int param2)
{
    int local;
    int object;

    obj->unk_20 = 0;
    obj->unk_1B = 9;
    obj->unk_24 = -1;
    obj->unk_14 = 0;
    obj->unk_17 = 0xFF;
    obj->unk_18 = 0;
    obj->unk_28 = -1;
    obj->unk_2C = 0x64;
    obj->unk_30 = 0x64;
    func_ov095_0229b3ec(obj);
    if (param2 == 0) {
        func_ov095_022999a8(obj, 4);
        obj->unk_44 = (void *) &data_ov095_0229e6b4;
    } else {
        obj->unk_44 = (void *) &data_ov095_0229e6e4;
    }
    obj->unk_42 = (unsigned char) param2;
    obj->unk_19 = 0x0c;
    obj->unk_1A = 0x0c;
    obj->unk_16 = 0x04;
    if ((object = func_020984e8()) != 0) {

        if (func_020950c0((void *) func_02099870(object)) == 0) {
            func_0200458c(0);
            return;
        }
    }
    func_0200458c(1);
}
