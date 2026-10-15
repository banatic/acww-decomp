/* func_ov103_0229d080 @ 0x0229d080, 0x38 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(void *p, int a);
extern unsigned char *func_ov002_02208098(void *p, unsigned char c);
extern void func_0208e5cc(void *p);

struct BigStruct {
    char pad_00[0x2274];
    int unk_2274;
    char pad_2278[0x454];
    int unk_26CC;
    char pad_26D0[0x6d7];
    unsigned char unk_2DA7;
};

void func_ov103_0229d080(struct BigStruct *this)
{
    if (func_ov002_0220b8ac(&this->unk_26CC, 0)) {
        func_ov002_02208098(this, this->unk_2DA7);
        func_0208e5cc(&this->unk_2274);
    }
}
