/* func_0203e8c0 @ 0x0203e8c0, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ef90(unsigned int);
extern int func_02096174(void);
extern void func_0203ead0(int, unsigned char);

struct UnkStruct_0203e8c0 {
    unsigned char pad_00[0x10];
    unsigned int unk_10;
    unsigned char pad_14[2];
    unsigned char state;
    unsigned char unk_17;
};

int func_0203e8c0(struct UnkStruct_0203e8c0 *p)
{
    int r = func_0203ef90(p->unk_10);
    switch (p->state) {
        case 4:
            if (func_02096174() != 0) {
                func_0203ead0(r, p->unk_17);
                p->state = 5;
            }
            break;
        case 5:
            break;
        case 6:
            return 1;
    }
    return 0;
}
