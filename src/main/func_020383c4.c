/* func_020383c4 @ 0x020383c4, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02001b60(void);
extern int func_02001b28(void);
extern int func_02001bd0(void);
extern int func_02001b98(void);
extern void func_02001b54(int);
extern void func_02001b1c(int);
extern void func_02001bc4(int);
extern void func_02001b8c(int);

struct UnkStruct_020383c4 {
    char pad_00[0xca];
    unsigned char ca;
    unsigned char cb;
    char pad_CC[0x0d0 - 0xcc];
    int d0;
    int d4;
    int d8;
    int dc;
};

void func_020383c4(struct UnkStruct_020383c4 *self)
{
    if (self->ca == 0) {
        self->ca = 1;
        self->d0 = func_02001b60();
        self->d4 = func_02001b28();
        self->d8 = func_02001bd0();
        self->dc = func_02001b98();
        func_02001b54(1);
        func_02001b1c(0);
        func_02001bc4(0);
        func_02001b8c(0);
        self->cb = 1;
    }
}
