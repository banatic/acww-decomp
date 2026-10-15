/* func_02022c2c @ 0x02022c2c, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02022c2c;
typedef int (UnkStruct_02022c2c::*PMF)(void);

struct UnkStruct_02022c2c_2 {
    unsigned char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02022c2c {
    unsigned char pad_00[0x100];
    UnkStruct_02022c2c_2 *unk_100;
};

extern PMF data_020d9410, data_020d9400, data_020d93f0, data_020d93e8, data_020d93e0, data_020d93c8, data_020d93b8,
    data_020d93b0;
extern volatile unsigned char data_020e54a8;

extern "C" int func_0207f1c8(int);
extern "C" int func_0209b5ec(void *);
extern "C" int func_0209c330(int);
extern "C" int func_0209c38c(int);

extern "C" int func_02022c2c(UnkStruct_02022c2c *obj)
{
    static PMF tbl[8] = {data_020d9410, data_020d9400, data_020d93f0, data_020d93e8,
                         data_020d93e0, data_020d93c8, data_020d93b8, data_020d93b0};
    int idx;
    int t;
    int v;

    idx = 8;
    t = (data_020e54a8 == 0);
    if (t) {
        v = obj->unk_100->unk_830;
        if (v) {
            idx = func_0209c330((func_0209b5ec((void *) func_0207f1c8(v))));
        }
    }
    if (func_0209c38c(idx)) {
        return (obj->*tbl[idx])();
    }
    return 0;
}
