/* func_020bc8ac @ 0x020bc8ac, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2F30];
    int unk_2F30;
} UnkStruct_020bc8ac;

extern void func_020bca80(UnkStruct_020bc8ac *p, int a, int b, int c);
extern void func_020bc9c4(UnkStruct_020bc8ac *p, int a);
extern void func_020bcc70(UnkStruct_020bc8ac *p);

void func_020bc8ac(UnkStruct_020bc8ac *p)
{
    int val = p->unk_2F30;
    if (val < 0) {
        func_020bca80(p, 0xA0, 0x64, 500);
    } else {
        if (val == 0) {
            func_020bc9c4(p, 0x14);
        }
    }
    func_020bcc70(p);
}
