/* func_0201bcec @ 0x0201bcec, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201bcec {
    char pad_00[0x4e8];
    unsigned int unk_4E8;
    char pad_4EC[0x563 - 0x4e8 - 4];
    unsigned char unk_563;
    char pad_564[0x62c - 0x563 - 1];
    unsigned char unk_62C;
} UnkStruct_0201bcec;

extern int func_020a7278(UnkStruct_0201bcec *self);
extern void func_0201bf24(UnkStruct_0201bcec *self, int arg);
extern void func_0203f004(UnkStruct_0201bcec *self, int arg);

void func_0201bcec(UnkStruct_0201bcec *self, int arg2)
{
    if (arg2 == 2) {
        if (func_020a7278(self) == 0) {
            if ((self->unk_4E8 & 2) == 0) {
                self->unk_4E8 |= 2;
                self->unk_62C = 1;
            }
        }
        if (self->unk_563 == 0) {
            func_0201bf24(self, 1);
        }
    }
    func_0203f004(self, arg2);
}
