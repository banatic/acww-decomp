/* func_0203aeec @ 0x0203aeec, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203aeec {
    char pad_00[0x21c];
    unsigned int unk_21C;
};

extern struct UnkStruct_0203aeec *data_021c67a4;
extern int func_0203c0ac(struct UnkStruct_0203aeec *p, int n);

void func_0203aeec(unsigned int value)
{
    data_021c67a4->unk_21C = value;
    func_0203c0ac(data_021c67a4, 0x11);
}
