/* func_ov107_0229c7b0 @ 0x0229c7b0, 0x74 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d0f0(void *, unsigned char);
extern int func_0206fca4(void);
extern int func_020435a0(int, int);
extern int func_02043568(int, int);
extern void func_ov107_0229d480(void *);
extern void func_ov107_0229d3a0(void *, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

struct UnkStruct_0229c7b0 {
    unsigned char pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_0229c7b0 *data_020ccf94;

struct UnkStruct_0229c7b0_2 {
    unsigned char pad_00[0xac];
    int unk_AC;
    unsigned char pad_B0[0xb9 - (0xac + 4)];
    unsigned char unk_B9;
};

void func_ov107_0229c7b0(struct UnkStruct_0229c7b0_2 *self)
{
    int result;

    result = func_ov107_0229d0f0(self, self->unk_B9);

    if (func_0206fca4() == 0x29) {
        self->unk_AC = func_020435a0(data_020ccf94->unk_64, result);
    } else {
        self->unk_AC = func_02043568(data_020ccf94->unk_64, result);
    }

    if (self->unk_AC == -1) {
        func_ov107_0229d480(self);
        func_ov107_0229d3a0(self, 3, 0xff);
    } else {
        func_ov002_02208098((void *) (self), 0x15);
    }
}
