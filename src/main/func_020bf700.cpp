/* func_020bf700 @ 0x020bf700, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bf700;
typedef void (UnkStruct_020bf700::*PMF)(void);
struct UnkStruct_020bf700 {
    int idx;
};

extern PMF data_020e5c90, data_020e5a80, data_020e5be8, data_020e5ca8, data_020e5cf8, data_020e5d00, data_020e5cb0;
extern PMF data_020e5b70, data_020e59f8, data_020e5d68, data_020e5ad8, data_020e5ae0, data_020e5d18;

extern int data_021f6cd4;
extern PMF data_021f6e68[13];

extern "C" void func_020bf700(UnkStruct_020bf700 *p)
{
    if (!(data_021f6cd4 & 1)) {
        data_021f6e68[0] = data_020e5c90;
        data_021f6e68[1] = data_020e5a80;
        data_021f6e68[2] = data_020e5be8;
        data_021f6e68[3] = data_020e5ca8;
        data_021f6e68[4] = data_020e5cf8;
        data_021f6e68[5] = data_020e5d00;
        data_021f6e68[6] = data_020e5cb0;
        data_021f6e68[7] = data_020e5b70;
        data_021f6e68[8] = data_020e59f8;
        data_021f6e68[9] = data_020e5d68;
        data_021f6e68[10] = data_020e5ad8;
        data_021f6e68[11] = data_020e5ae0;
        data_021f6e68[12] = data_020e5d18;
        data_021f6cd4 |= 1;
    }
    PMF f;

    f = data_021f6e68[p->idx];
    if (f) {
        (p->*f)();
    }
}
