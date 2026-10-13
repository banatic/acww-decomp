/* func_020f2814 @ 0x020f2814, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *p);
extern char data_0213eeb0;

struct UnkStruct_020f2814 {
    void *unk_00;
    unsigned char unk_04;
};

void *func_020f2814(struct UnkStruct_020f2814 *p)
{
    func_020f45c4(p);
    p->unk_00 = &data_0213eeb0;
    p->unk_04 = 0x33;
    return p;
}
