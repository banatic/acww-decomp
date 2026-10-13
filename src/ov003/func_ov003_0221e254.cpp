/* func_ov003_0221e254 @ 0x0221e254, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221e254 {};

typedef void (UnkStruct_0221e254::*TPMF)();

extern TPMF data_ov003_022393ec;
extern TPMF data_ov003_02239414;
extern TPMF data_ov003_02239424;
extern TPMF data_ov003_022393ac;
extern TPMF data_ov003_022393dc;
extern TPMF data_ov003_022393f4;
extern TPMF data_ov003_02239464;

extern "C" int func_02056f28(void *, int);
extern "C" void func_ov009_02262ef0(void *, int);

extern "C" void func_ov003_0221e254(UnkStruct_0221e254 *self)
{
    static int guard;
    static TPMF tbl[7];

    if ((guard & 1) == 0) {
        tbl[0] = data_ov003_022393ec;
        tbl[1] = data_ov003_02239414;
        tbl[2] = data_ov003_02239424;
        tbl[3] = data_ov003_022393ac;
        tbl[4] = data_ov003_022393dc;
        tbl[5] = data_ov003_022393f4;
        tbl[6] = data_ov003_02239464;
        guard |= 1;
    }

    {
        unsigned char idx = ((unsigned char *) self)[0x134];
        if (idx < 7) {
            (self->*tbl[idx])();
        }
    }

    if (func_02056f28((char *) self + 0x2b8, 0x12)) {
        func_ov009_02262ef0((char *) self + 0x238, 0x7de);
    }
}
