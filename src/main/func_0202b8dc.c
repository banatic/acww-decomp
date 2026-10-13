/* func_0202b8dc @ 0x0202b8dc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0202b8dc UnkStruct_0202b8dc;
struct UnkStruct_0202b8dc {
    unsigned char pad_00[0x824];
    unsigned char unk_824;
    unsigned char pad_825[0x830 - 0x824 - 1];
    int unk_830;
};

typedef struct UnkStruct_0202b8dc_2 UnkStruct_0202b8dc_2;
struct UnkStruct_0202b8dc_2 {
    char pad_00[0x100];
    UnkStruct_0202b8dc *sub;
};

typedef struct GlobalData {
    int unk_00;
    unsigned char unk_04;
} GlobalData;

extern GlobalData data_020c8b18;
extern void func_0208150c(int arg);
extern int func_020036e8(void);
extern void func_0202da38(UnkStruct_0202b8dc_2 *this, char *p1, char *p2, int size, int a, int b, int c, int d, int e);
extern void func_0202da88(UnkStruct_0202b8dc_2 *this, char *p);
extern char data_021c2704[];

int func_0202b8dc(UnkStruct_0202b8dc_2 *this)
{
    UnkStruct_0202b8dc *sub;
    int ret0;
    int local1;
    int local2;
    int local3;
    int local4;
    GlobalData *g;

    sub = this->sub;
    func_0208150c(sub->unk_830);
    ret0 = func_020036e8();
    g = &data_020c8b18;
    local1 = g->unk_00;
    local2 = 9;
    local3 = sub->unk_824 & 1;
    local4 = g->unk_04;

    func_0202da38(this, (char *) this + 0x104, (char *) this + 0x122, 0x1e, ret0, local1, local2, local3, local4);
    func_0202da88(this, data_021c2704);
    return 1;
}
