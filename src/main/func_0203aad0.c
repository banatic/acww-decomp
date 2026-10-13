/* func_0203aad0 @ 0x0203aad0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1ec];
    int unk_1EC;
    int unk_1F0;
} UnkStruct_0203aad0;

extern UnkStruct_0203aad0 *data_021c67a4;
extern void func_0203ad58(void);

int func_0203aad0(int a, int b)
{
    UnkStruct_0203aad0 *p = data_021c67a4;
    if (p != 0) {
        if (p->unk_1EC != b || p->unk_1F0 != a) {
            func_0203ad58();
            data_021c67a4->unk_1F0 = a;
            data_021c67a4->unk_1EC = b;
            return 1;
        }
        return 0;
    }
    return 0;
}
