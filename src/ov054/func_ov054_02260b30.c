/* func_ov054_02260b30 @ 0x02260b30, 0x3e bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_020160b4(void *arg0);
extern int func_020ab504(void *);
extern int func_020984e8(void);
extern void func_0203d480(int);
extern void func_0203d394(void);

struct UnkStruct_02260b30 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

void func_ov054_02260b30(struct UnkStruct_02260b30 *obj, unsigned int callbackArgument1)
{
    int v;

    v = func_020ab504((void *) func_020160b4((void *) obj));
    func_020984e8();

    if (obj->unk_1E == 0x12) {
        switch (v) {
            case 0:
                func_0203d480(0);
                break;
            case 1:
                func_0203d480(1);
                break;
        }
        func_0203d394();
    }
}
