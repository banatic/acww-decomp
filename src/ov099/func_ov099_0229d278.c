/* func_ov099_0229d278 @ 0x0229d278, 0x44 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d278 UnkStruct_0229d278;
struct UnkStruct_0229d278 {
    unsigned char pad_00[0x2274];
    unsigned char sub[0x696];
    unsigned char unk_290A;
};
extern int func_0208e484(const void *ptr);
extern int func_ov002_02209f9c(const void *ptr);
extern unsigned char *func_ov002_02208098(UnkStruct_0229d278 *self, unsigned char byte);
extern void func_ov099_0229c28c(UnkStruct_0229d278 *self, int value);
extern void func_ov099_0229c928(UnkStruct_0229d278 *self);

void func_ov099_0229d278(UnkStruct_0229d278 *self)
{
    if (func_0208e484(self->sub)) {
        func_ov002_02208098(self, self->unk_290A);
    }
    if (func_ov002_02209f9c(self->sub)) {
        func_ov099_0229c28c(self, 0x40);
        func_ov099_0229c928(self);
    }
}
