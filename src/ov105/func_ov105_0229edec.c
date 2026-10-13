/* func_ov105_0229edec @ 0x0229edec, 0x44 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int x);
extern void func_020027f0(int x);
extern void func_ov105_0229c4cc(void *p);
extern void func_ov002_02208090(void *p, int x);
extern void func_ov105_0229ed78(void *p);

struct UnkStruct_0229edec {
    char pad_00[0x2c1];
    unsigned char counter;
};

void func_ov105_0229edec(struct UnkStruct_0229edec *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(4);
        if (param->counter != 0) {
            param->counter--;
        } else {
            func_ov105_0229c4cc(param);
            func_ov002_02208090(param, 0xd);
        }
    } else {
        func_ov105_0229ed78(param);
    }
}
