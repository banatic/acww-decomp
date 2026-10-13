/* func_0201ca54 @ 0x0201ca54, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201cb68(void *p, int q);
extern void func_0201cab8(void *p, int q);

struct UnkStruct_0201ca54 {
    char pad_00[0x48];
    unsigned char unk_48;
};

void func_0201ca54(struct UnkStruct_0201ca54 *p0, int p1)
{
    if (func_0201cb68(p0, p1) != 0) {
        if (p0->unk_48 == 0) {
            func_0201cab8(p0, p1);
        }
        p0->unk_48 = p0->unk_48 + 1;
        if (p0->unk_48 >= 20U) {
            p0->unk_48 = 0;
        }
    }
}
