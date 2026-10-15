/* func_ov121_02299c10 @ 0x02299c10, 0x78 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299c10 {
    unsigned char pad_00[0xB5];
    unsigned char unk_B5;
    unsigned char unk_B6;
} UnkStruct_02299c10;

extern int func_ov121_02299a5c(UnkStruct_02299c10 *, int);
extern void func_ov121_02299a3c(UnkStruct_02299c10 *, int);
extern void func_ov121_0229af00(UnkStruct_02299c10 *, unsigned char, int);

void func_ov121_02299c10(UnkStruct_02299c10 *p)
{
    if (func_ov121_02299a5c(p, 0x200)) {
        if (p->unk_B6) {
            p->unk_B6--;
            switch (p->unk_B6 % 5) {
                case 0:
                    func_ov121_0229af00(p, p->unk_B5, 2);
                    break;
                case 3:
                    func_ov121_0229af00(p, p->unk_B5, 6);
                    break;
            }
        } else {
            func_ov121_02299a3c(p, 0x200);
            func_ov121_0229af00(p, p->unk_B5, 2);
        }
    }
}
