/* func_02022674 @ 0x02022674, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02022674 {
    char pad_00[0x830];
    int data;
};

class UnkStruct_02022674_2 {
  public:
    char pad_00[0x100];
    UnkStruct_02022674 *inner;
};

typedef int (UnkStruct_02022674_2::*PMF)();

extern PMF data_020d92d8;
extern PMF data_020d8fa8;
extern PMF data_020d92e0;
extern PMF data_020d9298;
extern PMF data_020d93a0;
extern PMF data_020d8fa0;
extern PMF data_020d91e0;
extern PMF data_020d9288;

extern int data_021c1cec;
extern unsigned char data_020e54a8;

extern "C" int func_0207f270(int);
extern "C" int func_020794cc(int);
extern "C" int func_0209c38c(int);

extern PMF data_021c1ec4[8];

extern "C" int func_02022674(UnkStruct_02022674_2 *self)
{
    if ((data_021c1cec & 1) == 0) {
        data_021c1ec4[0] = data_020d92d8;
        data_021c1ec4[1] = data_020d8fa8;
        data_021c1ec4[2] = data_020d92e0;
        data_021c1ec4[3] = data_020d9298;
        data_021c1ec4[4] = data_020d93a0;
        data_021c1ec4[5] = data_020d8fa0;
        data_021c1ec4[6] = data_020d91e0;
        data_021c1ec4[7] = data_020d9288;
        data_021c1cec |= 1;
    }

    unsigned int ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok > 0) {
        int a = func_0207f270(self->inner->data);
        int b = func_020794cc(a);
        if (func_0209c38c(b) != 0) {
            return (self->*data_021c1ec4[b])();
        }
    }
    return 0;
}
