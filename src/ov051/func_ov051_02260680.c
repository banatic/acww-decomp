/* func_ov051_02260680 @ 0x02260680, 0x48 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov051_022614c0[];
extern int data_ov051_022615c0;

extern int func_ov051_022605e8(void *p, unsigned char b);
extern void func_0206844c(int a, unsigned char *b, int c);

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    int *unk_B0;
} UnkStruct_02260680;

void func_ov051_02260680(UnkStruct_02260680 *param1, int param2)
{
    unsigned char ch;

    ch = (unsigned char) func_ov051_022605e8(param1, data_ov051_022614c0[param2]);
    func_0206844c(param1->unk_40, &ch, data_ov051_022615c0);

    if (param2 == 1) {
        *(int *) ((char *) param1->unk_B0 + 0x714) += 2;
    }
}
