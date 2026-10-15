/* func_ov003_022197c4 @ 0x022197c4, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern int func_02073908(void *, int);
extern int func_02008258(void *, int);
extern int func_0203e140(void);
extern int func_0200d4e8(void *, int, int, int);
extern int func_ov003_02210154(void *, int, int);

struct UnkStruct_022197c4_2 {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};
struct UnkStruct_022197c4 {
    char pad_00[0x68];
    int unk_68;
};
extern struct UnkStruct_022197c4 *data_020ccf94;

int func_ov003_022197c4(int a, int b)
{
    struct UnkStruct_022197c4_2 *o = (struct UnkStruct_022197c4_2 *) func_02096718(b);
    if (b == 4) {
        b = data_020ccf94->unk_68;
    }
    if (o != 0) {
        if (func_02073908(data_020ccf94, b) != 0) {
            o->unk_7FC = func_02008258(o, o->unk_7F0);
            switch (a) {
                case 0:
                    func_0203e140();
                    func_0200d4e8(o, 3, 1, -1);
                    break;
                case 1:
                    func_ov003_02210154(o, 6, -1);
                    break;
            }
        }
        return 1;
    }
    return 0;
}
