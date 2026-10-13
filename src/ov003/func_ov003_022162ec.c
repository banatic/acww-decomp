/* func_ov003_022162ec @ 0x022162ec, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022162ec {
    char pad_00[0x800];
    int unk_800;
};
extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_020984fc(int);
extern unsigned short *func_02099728(int);
extern void func_0200f1a4(struct UnkStruct_022162ec *, int, unsigned short);
extern void func_02045f08(int *, int);
extern void func_0200f268(struct UnkStruct_022162ec *, int);
void func_ov003_022162ec(struct UnkStruct_022162ec *p)
{
    unsigned short *msg;
    unsigned char *xy;
    unsigned char y;
    int pos[2];

    if (func_02073908(data_020ccf94, p->unk_800) != 0) {
        msg = func_02099728(func_020984fc(p->unk_800));
        if (msg != 0) {
            func_0200f1a4(p, 3, *msg);
        }
    } else {
        xy = (unsigned char *) p + 0x7d4;
        if (xy[2] != 0) {
            y = xy[1];
            pos[0] = xy[0];
            pos[1] = y;
            func_02045f08(pos, 0);
            func_0200f268(p, 0x12);
        }
    }
}
