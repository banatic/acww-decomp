/* func_0209b4d8 @ 0x0209b4d8, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0209b4d8 {
  public:
    virtual void v0();
};

typedef void (UnkStruct_0209b4d8::*PMF)();

struct PMFEntry {
    PMF pmf;
    int pad_08[3];
};
extern PMFEntry data_020e3504[];
extern "C" int func_0209bc94(int);
extern "C" int func_0209bc54(int *, int);
extern "C" void func_0209bd30(UnkStruct_0209b4d8 *, int, unsigned short *, int);
extern "C" void func_02003728(void *, void *);

extern "C" int func_0209b4d8(UnkStruct_0209b4d8 *p0, int p1, void *p2, void *p3)
{
    unsigned short val;
    int idx = 0;
    int result = 0;
    if (func_0209bc94(p1) == 1) {
        if (func_0209bc54(&idx, p1) != 0) {
            val = 0xfff1;
            func_0209bd30(p0, p1, &val, 0);
            PMFEntry *e = &data_020e3504[idx];
            if (e->pmf) {
                (p0->*e->pmf)();
            }
            if (p2) {
                func_02003728((char *) p0 + 0xc, p2);
            }
            if (p3) {
                p0 = (UnkStruct_0209b4d8 *) ((char *) p0 + 0x1c);
                func_02003728(p0, p3);
            }
            result = 1;
        }
    }
    return result;
}
