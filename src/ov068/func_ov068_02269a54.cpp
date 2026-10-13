/* func_ov068_02269a54 @ 0x02269a54, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02269a54 {
  public:
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    int method(int arg);
};

typedef int (UnkStruct_02269a54::*PMF)(int);

extern PMF data_ov068_02277048;
extern PMF data_ov068_02277060;
extern PMF data_ov068_02277068;
extern PMF data_ov068_02277078;

extern "C" int func_ov068_02269a54(UnkStruct_02269a54 *p, int arg)
{
    static PMF table[4];
    static int init_done = 0;
    if (!(init_done & 1)) {
        table[0] = data_ov068_02277048;
        table[1] = data_ov068_02277060;
        table[2] = data_ov068_02277068;
        table[3] = data_ov068_02277078;
        init_done |= 1;
    }
    unsigned char index = p->unk_1C;
    if (index < 4) {
        (p->*table[index])(arg);
    }
    return 0;
}
