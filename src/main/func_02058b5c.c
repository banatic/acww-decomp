/* func_02058b5c @ 0x02058b5c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cbaec[];
extern unsigned char data_021c933c[];
extern void func_0205967c(void *a, void *b);
extern void VEC_Add(void *a, void *b, void *c);
extern int _s32_div_f(unsigned int a, unsigned char b);

struct UnkStruct_02058b5c {
    char pad_00[0x60];
    char unk_60[0x24];
    char unk_84[0x24];
    unsigned int unk_A8;
    char pad_AC[0x14];
    int unk_C0;
    char pad_C4[0x10];
    unsigned char unk_D4;
    char pad_D5;
    unsigned short unk_D6;
};

void func_02058b5c(struct UnkStruct_02058b5c *s)
{
    if (s->unk_D6 < data_020cbaec[s->unk_D4]) {
        func_0205967c(s, s->unk_60);
        VEC_Add(s->unk_60, s->unk_84, s->unk_60);
        s->unk_D6++;
        if (s->unk_D6 >= data_020cbaec[s->unk_D4]) {
            int res = _s32_div_f(s->unk_A8, data_021c933c[s->unk_D4]);
            if (res < 0) {
                res = -res;
            }
            s->unk_C0 = res;
            s->unk_D4++;
        }
    }
}
