/* func_0202afdc @ 0x0202afdc, 0x244 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0202afdc;
typedef int (UnkStruct_0202afdc::*PMF)(void);

struct UnkStruct_0202afdc_2 {
    void *p;
    unsigned char b;
};
struct UnkStruct_0202afdc_3 {
    char pad_00[0x830];
    int unk_830;
};

class UnkStruct_0202afdc {
  public:
    char pad_00[0x100];
    UnkStruct_0202afdc_3 *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x105];
    unsigned char unk_122;
    char pad_123[1];
    unsigned short unk_124;
    char pad_126[0x128 - 0x126];
    char unk_128;
    char pad_129[0x12c - 0x129];
    char unk_12C;
    char pad_12D[0x16c - 0x12d];
    PMF unk_16C;
    PMF unk_174;
    PMF unk_17C;
    PMF unk_184;
    PMF unk_18C;
    char pad_194[0x19c - 0x194];
    unsigned short unk_19C;
};

extern PMF data_020d8ec8, data_020d8ea8, data_020d8dd8, data_020d8ed8, data_020d8de0, data_020d8dd0, data_020d8eb0,
    data_020d9088, data_020d9258;
extern PMF data_020d93a8, data_020d9160, data_020d9148, data_020d91e8, data_020d90d0;
extern unsigned char data_020c8e68[];

extern "C" void MI_CpuCopy8(const void *, void *, int);
extern "C" void func_0202d8f8(UnkStruct_0202afdc *, void *, void *, int, int);
extern "C" int func_0202114c(UnkStruct_0202afdc *, unsigned char *, int);
extern "C" int func_020644cc(int);
extern "C" int func_0202bd7c(UnkStruct_0202afdc *, int, int);
extern "C" void func_02015de4(UnkStruct_0202afdc *, void *, int, int);

extern "C" void func_0202afdc(UnkStruct_0202afdc *s, UnkStruct_0202afdc_2 *out);

extern int data_021c1cfc;
extern PMF data_021c1f4c[9];

extern "C" void func_0202afdc(UnkStruct_0202afdc *s, UnkStruct_0202afdc_2 *out)
{
    if (!(data_021c1cfc & 1)) {
        data_021c1f4c[0] = data_020d8ec8;
        data_021c1f4c[1] = data_020d8ea8;
        data_021c1f4c[2] = data_020d8dd8;
        data_021c1f4c[3] = data_020d8ed8;
        data_021c1f4c[4] = data_020d8de0;
        data_021c1f4c[5] = data_020d8dd0;
        data_021c1f4c[6] = data_020d8eb0;
        data_021c1f4c[7] = data_020d9088;
        data_021c1f4c[8] = data_020d9258;
        data_021c1cfc |= 1;
    }
    unsigned char flags[9];
    int ret;
    int i;

    ret = 0;
    MI_CpuCopy8(data_020c8e68, flags, 9);
    func_0202d8f8(s, &s->unk_12C, &s->unk_128, s->unk_100->unk_830, ret);
    while (ret == 0) {
        i = func_0202114c(s, flags, 9);
        if (i >= 0 && i < 9) {
            ret = (s->*data_021c1f4c[i])();
            if (ret == 0) {
                flags[i] = 0;
            }
        } else {
            (s->*data_021c1f4c[func_020644cc(2)])();
            break;
        }
    }
    out->p = &s->unk_104;
    out->b = s->unk_122;
    func_0202bd7c(s, 4, 3);
    func_0202bd7c(s, 6, 4);
    if (s->unk_124 != 0xfff1) {
        func_02015de4(s, &s->unk_124, 0, 7);
    }
    if (s->unk_19C != 0xfff1) {
        func_02015de4(s, &s->unk_19C, 1, 7);
        func_02015de4(s, &s->unk_19C, 2, 7);
    }
    s->unk_16C = data_020d93a8;
    s->unk_174 = data_020d9160;
    s->unk_17C = data_020d9148;
    s->unk_184 = data_020d91e8;
    s->unk_18C = data_020d90d0;
}
