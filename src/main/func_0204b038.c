/* func_0204b038 @ 0x0204b038, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204b038 {
    int value;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    unsigned char pad_10[16];
    signed int flag : 1;
};

void func_0204b038(struct UnkStruct_0204b038 *s)
{
    int sum = s->unk_04 + s->unk_06 + s->unk_05 + s->unk_07;
    s->value = 100;
    if (sum > 15) {
        s->value += -2 * (sum - 15);
    } else if (sum < 12) {
        s->value += -2 * (12 - sum);
    }
    if (s->unk_08 >= 3) {
        s->value -= s->unk_08 - 2;
    }
    if (s->unk_0A >= 3) {
        s->value -= s->unk_0A - 2;
    }
    s->value += -10 * s->unk_0C;
    if (s->flag == 1) {
        s->value -= 50;
    }
    if (s->unk_0E >= 3) {
        s->value += s->unk_0E - 2;
    }
}
