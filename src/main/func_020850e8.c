/* func_020850e8 @ 0x020850e8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02085174(void *p, int, int);
extern int func_02073dd4(void *p, int field);
extern void func_020771cc(int a, void *b, int c, int d);

struct UnkStruct_020850e8 {
    char pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_020850e8 *data_020ccf94;

void func_020850e8(int x, int y, int z, unsigned short *p)
{
    func_02085174(p, y, z);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
        unsigned short val = *p;
        int high = (val & 0xf000) >> 12;
        int low = val & 0xfff;
        if (high == 0xe) {
            low += 0xc;
            func_020771cc(low, &x, 0, 0);
        } else if (high == 0xd) {
            low += 0x20;
            func_020771cc(low, &x, 0, 0);
        }
    }
}
