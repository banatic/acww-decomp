/* func_020eefd4 @ 0x020eefd4, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct020eefd4 {
    unsigned char pad_00[0x15];
    unsigned char unk_15;
    unsigned char pad_16[6];
    int unk_1C;
};

extern void OS_Terminate(void);
extern void func_020eec60(int);

void func_020eefd4(struct UnkStruct020eefd4 *self)
{
    if (self->unk_15 == 0xff) {
        OS_Terminate();
    }
    if (self->unk_1C == 0xff) {
        return;
    }
    func_020eec60(self->unk_1C);
}
