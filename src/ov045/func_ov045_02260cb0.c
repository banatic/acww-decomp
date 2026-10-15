/* func_ov045_02260cb0 @ 0x02260cb0, 0x64 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019df8(unsigned int);
extern int func_02019e00(unsigned int);
extern void func_02035624(int);
extern int func_02016014(void *, int);
extern int func_ov004_02230518(void);
extern int func_ov004_022304f8(void);
extern int func_ov004_022304d8(void);

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned int unk_B4;
} UnkStruct_02260cb0;

void func_ov045_02260cb0(UnkStruct_02260cb0 *self, int key)
{
    if (key == func_02019df8(self->unk_B4 + 0x564) && func_02019e00(self->unk_B4 + 0x564) == 8) {
    } else {
        switch (key) {
            case 0x1e:
                func_ov004_02230518();
                break;
            case 0x1f:
                func_02035624(0x10);
                func_ov004_022304f8();
                break;
            case 0x20:
                func_ov004_022304d8();
                break;
        }
    }
    func_02016014(self, key);
}
