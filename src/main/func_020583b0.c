/* func_020583b0 @ 0x020583b0, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x60];
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned int unk_68;
    unsigned int unk_6C;
    unsigned int unk_70;
    unsigned int unk_74;
    char pad_78[0x90 - 0x78];
    unsigned int unk_90;
    unsigned int unk_94;
    unsigned int unk_98;
    char pad_9C[0xd6 - 0x9c];
    unsigned short unk_D6;
} Context;

extern void func_020e895c(void *a, void *b, void *c);
extern void func_02059674(void *this, int param);

void func_020583b0(Context *this)
{
    if ((int) this->unk_D6 < 2) {
        func_020e895c(&this->unk_60, (void *) this->unk_6C, (void *) this->unk_90);
        func_020e895c(&this->unk_64, (void *) this->unk_70, (void *) this->unk_94);
        func_020e895c(&this->unk_68, (void *) this->unk_74, (void *) this->unk_98);
        this->unk_D6++;
        if ((int) this->unk_D6 >= 2) {
            func_02059674(this, 0);
        }
    }
}
