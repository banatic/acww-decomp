/* func_02028924 @ 0x02028924, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02028924;
typedef int (UnkStruct_02028924::*PMF)(void *, int);

struct UnkStruct_02028924_2 {
    unsigned char pad_00[0x830];
    void *unk_830;
};
struct ST {
    int pad_00[8];
    unsigned char a, b;
    unsigned char pad_22[2];
};
struct UnkStruct_02028924_3 {
    int x, y;
};

struct UnkStruct_02028924 {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0x100 - 0x44];
    UnkStruct_02028924_2 *unk_100;
};

extern PMF data_020d9108, data_020d94c0, data_020d9198, data_020d91b0, data_020d91b8;
extern int data_020c8928, data_021c1e14, data_020c8924, data_021c1d6c;
extern UnkStruct_02028924_3 data_020d9188;

extern "C" void func_020984e8(void);
extern "C" int func_02099640(void);
extern "C" void func_0201cf74(UnkStruct_02028924 *, ST *, int, void *, void *);
extern "C" void func_0201cec8(UnkStruct_02028924 *, ST *);
extern "C" void func_0202da74(UnkStruct_02028924 *, UnkStruct_02028924_3);
extern "C" void func_02068388(int, int);

extern "C" void func_02028924(UnkStruct_02028924 *p)
{
    static PMF tbl[5] = {data_020d9108, data_020d94c0, data_020d9198, data_020d91b0, data_020d91b8};
    ST st;
    void *a;
    int b;
    int i;

    a = p->unk_100->unk_830;
    func_020984e8();
    b = func_02099640();
    for (i = 0; i < 5; i++) {
        if ((p->*tbl[i])(a, b)) {
            break;
        }
    }
    if (i == 5) {
        func_0201cf74(p, &st, 0, &data_020c8928, &data_021c1e14);
        func_0201cf74(p, &st, 1, &data_020c8924, &data_021c1d6c);
        st.a = 2;
        st.b = st.a - 1;
        func_0201cec8(p, &st);
        func_0202da74(p, data_020d9188);
        func_02068388(p->unk_40, 1);
    }
}
