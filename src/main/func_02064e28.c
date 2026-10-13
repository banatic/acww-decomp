/* func_02064e28 @ 0x02064e28, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char pad_04[0x14 - 4];
    unsigned char unk_14;
    unsigned char pad_15[3];
    int unk_18;
    unsigned char unk_1C[0x30 - 0x1c];
    int unk_30;
} UnkStruct_02064e28;

typedef struct {
    unsigned char pad_00[0x50];
    int unk_50;
} UnkStruct_02064e28_2;

extern UnkStruct_02064e28_2 *data_021cd864;
extern void func_020650ac(UnkStruct_02064e28 *s);
extern int func_0206521c(unsigned char *p, int v);
extern void func_020b3670(void *p, int a, int b, int c, int d);
extern void func_020b36c8(void *p);
extern void func_02064ef8(UnkStruct_02064e28 *s);

void func_02064e28(UnkStruct_02064e28 *s)
{
    if (data_021cd864->unk_50 == 0) {
        func_020650ac(s);
        return;
    }
    if (func_0206521c(&s->unk_14, s->unk_00) != 0) {
        if (s->unk_14 != 0) {
            switch (s->unk_18) {
                case 0:
                case 3:
                    func_020b3670(&s->unk_1C, 1, 1, 0, 0x1000 / s->unk_30);
                    break;
                case 1:
                    func_020b3670(&s->unk_1C, 1, 1, 1, 0x800);
                    break;
                default:
                    func_020b3670(&s->unk_1C, 1, 0, 0, 0x800);
                    break;
            }
        } else {
            switch (s->unk_18) {
                case 0:
                case 3:
                    func_020b3670(&s->unk_1C, 0, 1, 0, 0x1000 / s->unk_30);
                    break;
                default:
                    func_020b3670(&s->unk_1C, 0, 0, 0, 0x800);
                    break;
            }
        }
    }
    func_020b36c8(&s->unk_1C);
    func_02064ef8(s);
}
