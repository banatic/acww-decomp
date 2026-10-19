/* func_020f7780 @ 0x020f7780, 0x144 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020f7780 {
    char pad_00[8];
    char h;
    char pad_09[0xd - 8 - 1];
    signed char d;
} UnkStruct_020f7780;

extern int func_020f7bc4(UnkStruct_020f7780 *self, int code, void *arg);
extern void func_020f7c1c(UnkStruct_020f7780 *self, void *p3);

void func_020f7780(UnkStruct_020f7780 *self, int msgId, void *p3)
{
    switch (msgId) {
        case 1:
            if (self->d == 0) {
                func_020f7bc4(self, 0x4f7, &self->h);
            }
            break;
        case 0x78:
            if (self->d == 1) {
                func_020f7bc4(self, 0x4f8, &self->h);
            }
            break;
        case 0xbe:
            if (self->d == 0) {
                func_020f7bc4(self, 0x4f9, &self->h);
            }
            break;
        case 0xd2:
            if (self->d == 1) {
                func_020f7bc4(self, 0x4fb, &self->h);
            }
            break;
        case 0x12c:
            if (self->d == 0) {
                func_020f7bc4(self, 0x4fa, &self->h);
            }
            break;
        case 0x15d:
            self->d++;
            if (self->d == 2) {
                self->d = 0;
            }
            break;
    }
    func_020f7c1c(self, p3);
}
