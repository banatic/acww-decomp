/* func_ov050_022614c8 @ 0x022614c8, 0x98 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_020ada14(void);
extern int func_0209ded0(void);
extern int func_020874c4(const void *p);
extern void func_02015fb0(void *a, int b, int c, int d, int e, int f);
extern unsigned char data_021f3b0c;

struct UnkStruct_022614c8 {
    char pad_00[0xd0];
    int unk_D0;
};

void func_ov050_022614c8(struct UnkStruct_022614c8 *obj, int val)
{
    func_020984e8();
    switch (val) {
        case 0:
            obj->unk_D0 = 7;
            break;
        case 1:
            if (func_0202e9fc() == 0) {
                obj->unk_D0 = 0x59;
            } else if (func_020ada14() != 0) {
                obj->unk_D0 = 0x18;
            } else {
                obj->unk_D0 = 0x17;
            }
            break;
        case 2:
            if (func_0209ded0() != 0) {
                int r = func_020874c4(&data_021f3b0c);
                func_02015fb0(obj, r, 1, 3, 0, 0);
                obj->unk_D0 = 0x16;
            } else {
                obj->unk_D0 = 0xd;
            }
            break;
        case 3:
            obj->unk_D0 = 0x15;
            break;
    }
}
