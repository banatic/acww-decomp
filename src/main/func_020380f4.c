/* func_020380f4 @ 0x020380f4, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc0];
    int unk_C0;
    int unk_C4;
    char pad_C8;
    unsigned char unk_C9;
    char pad_CA[26];
    int unk_E4;
} UnkStruct_020380f4;

extern int _s32_div_f(int a, int b);
extern void func_02038444(void *obj, int a, int b);
extern void func_0203859c(void *obj);
extern void func_02038680(void *obj, int a);
extern void func_020382b8(void *obj);
extern void func_020380c4(void *obj);

void func_020380f4(UnkStruct_020380f4 *obj)
{
    int temp = _s32_div_f(obj->unk_C0 + 0x13, 0x14);
    int changed = (obj->unk_E4 != temp);
    obj->unk_E4 = temp;

    if (obj->unk_C4 < 4) {
        func_02038444(obj, obj->unk_C4, 0);
        func_0203859c(obj);
        func_02038680(obj, obj->unk_C4);
        obj->unk_C4++;
    } else if (changed) {
        func_02038444(obj, 3, 0);
        func_0203859c(obj);
        func_02038680(obj, 3);
    }

    if (obj->unk_C9 == 0) {
        func_020382b8(obj);
    } else {
        obj->unk_C0--;
        if (obj->unk_C0 <= -20) {
            func_020380c4(obj);
        }
    }
}
