/* func_020421d0 @ 0x020421d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad_02[10];
    int unk_0C;
} Struct020421d0;

extern Struct020421d0 data_021c75b8;
extern int func_02001aac(int arg);

int func_020421d0(void)
{
    Struct020421d0 *p = &data_021c75b8;
    if (p->unk_00 == 3) {
        p->unk_0C = 0;
    } else {
        if (p->unk_01 == 0) {
            p->unk_0C = -16;
        } else {
            p->unk_0C = 0x10;
        }
    }
    return func_02001aac(p->unk_0C);
}
