/* func_ov003_02217d60 @ 0x02217d60, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200f268(void *p, int arg);
extern int func_ov003_022203ac(void);
extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern int func_0208602c(void);
extern int func_02086108(int a, int b);
extern int func_02073908(void *a, int b);
extern void func_02035684(int a, int b, int c);
extern void *data_020ccf94;

struct UnkStruct_02217d60 {
    char pad_00[0x7f8];
    int unk_7F8;
    char pad_7FC[0x4];
    int unk_800;
};

void func_ov003_02217d60(struct UnkStruct_02217d60 *p, void *message, int previous)
{
    int zero = 0;

    if (((void) (func_0200f268(p, 0)), func_ov003_022203ac()) != 0) {
        func_020109a0(p, 0x34, zero, zero);
    } else {
        func_020109a0(p, 0x35, zero, zero);
    }

    p->unk_7F8 = 0;

    if (func_02086108(func_0208602c(), 0) != 0 || func_02086108(func_0208602c(), 5) != 0) {
        if (func_02073908(data_020ccf94, p->unk_800) != 0) {
            func_02035684(0x12, 0xf, 0);
        }
    }
}
