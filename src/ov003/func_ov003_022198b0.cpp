/* func_ov003_022198b0 @ 0x022198b0, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

extern "C" int func_0203e21c(void);
extern "C" void *func_02096718(int);
extern "C" int func_0200f290(void *, int);
extern "C" int func_0200e7f8(void *);
extern "C" int func_0203e1c4(void);
extern "C" void *func_ov003_02215624(void *, int, int, int);
extern "C" int func_ov003_0220e05c(void *, int, int);

struct UnkStruct_022198b0 {
    char pad_00[0x7f0];
    int unk_7F0;
};

extern "C" int func_ov003_022198b0(void)
{
    if (func_0203e21c()) {
        return 0;
    }
    struct UnkStruct_022198b0 *o = (struct UnkStruct_022198b0 *) func_02096718(4);
    if (o) {
        if (func_0200f290(o, 0xb)) {
            return 0;
        }
        int mode = 5;
        if (mode <= func_0200e7f8(o)) {
            int x = o->unk_7F0;
            if (x != 0x4f) {
                return 0;
            }
            if (x == 0x4f) {
                func_ov003_02215624(o, 0, 6, ~0);
                return 0;
            }
        }
        if (!func_0203e1c4()) {
            return 0;
        }
        return func_ov003_0220e05c(o, 5, ~0);
    }
    return 0;
}
