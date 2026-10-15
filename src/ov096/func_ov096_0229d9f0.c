/* func_ov096_0229d9f0 @ 0x0229d9f0, 0x7c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d9f0 {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char pad_B7[0x358 - 0xb7];
    char unk_358;
} UnkStruct_0229d9f0;

extern unsigned short func_ov096_0229f0dc(UnkStruct_0229d9f0 *self, int b);
extern int func_ov096_0229daec(UnkStruct_0229d9f0 *self, int x);
extern int func_ov096_0229da6c(UnkStruct_0229d9f0 *self, int x);
extern int func_ov096_0229f7ac(UnkStruct_0229d9f0 *self, int b);
extern void func_ov096_0229fb9c(UnkStruct_0229d9f0 *self);
extern void func_ov096_0229f874(UnkStruct_0229d9f0 *self, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229c2ec(UnkStruct_0229d9f0 *self, int a);
extern void func_ov094_0229aa58(void *ptr, int y);

void func_ov096_0229d9f0(UnkStruct_0229d9f0 *self)
{
    unsigned char b;
    int r6;
    int x;
    int y;

    b = self->unk_B6;
    r6 = func_ov096_0229f0dc(self, b);
    if (func_ov096_0229daec(self, r6) == 0) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 9, 0xff, 1);
    } else {
        x = func_ov096_0229da6c(self, r6);
        if (x != 0) {
            if (x == 2) {
                func_ov002_02208098((void *) (self), 0x28);
                func_ov096_0229c2ec(self, 0x1000);
            } else {
                y = func_ov096_0229f7ac(self, b);
                func_ov094_0229aa58(&self->unk_358, y);
                func_ov096_0229fb9c(self);
            }
        }
    }
}
