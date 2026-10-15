/* func_ov102_0229dea4 @ 0x0229dea4, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov002_02207ce4(unsigned char *ptr, int val);
extern int func_ov102_0229c2a8(void *self, int val);
extern int func_ov102_0229cef8(void *self);
extern void func_ov102_0229d650(void *self, unsigned char byte);
extern void func_ov002_02207d00(unsigned char *ptr);

typedef struct UnkStruct_0229dea4 {
    unsigned char pad_00[0x218c];
    unsigned char sub[0x414];
    unsigned char flag;
} UnkStruct_0229dea4;

void func_ov102_0229dea4(UnkStruct_0229dea4 *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(self, 0);
        func_ov002_02207ce4(self->sub, 0x3c);
    } else {
        if (func_ov102_0229c2a8(self, 4) != 0 && func_ov102_0229cef8(self) != 0) {
            func_ov102_0229d650(self, self->flag);
        } else {
            func_ov002_02207d00(self->sub);
        }
    }
}
