/* func_ov121_0229bf38 @ 0x0229bf38, 0x94 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void func_ov121_0229b9d4(void *receiver);
extern void func_ov121_0229b968(struct UnkStruct_0229bf38 *);
}

struct UnkStruct_0229bf38 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
};

typedef void (UnkStruct_0229bf38::*PMF)();

extern PMF data_ov121_0229c338;
extern PMF data_ov121_0229c2a8;
extern PMF data_ov121_0229c2a0;
extern PMF data_ov121_0229c378;

extern "C" int func_ov121_0229bf38(UnkStruct_0229bf38 *self)
{
    static PMF pmf[4] = {data_ov121_0229c338, data_ov121_0229c2a8, data_ov121_0229c2a0, data_ov121_0229c378};
    func_ov121_0229b9d4(self);
    (self->*pmf[self->unk_8C])();
    func_ov121_0229b968(self);
    return 1;
}
