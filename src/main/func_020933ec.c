/* func_020933ec @ 0x020933ec, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *, int, int, int);
extern void func_0203423c(void *);
extern int func_020b6598(void);
extern int func_02094cf8(int, int, int, int, int, void *);

typedef struct {
    unsigned char pad_00[0x34];
    unsigned int unk_34;
    unsigned char pad_38[8];
} UnkStruct_020933ec;

extern unsigned char data_020e29dc[];

int func_020933ec(int arg1, int arg2, int arg3, int arg4)
{
    UnkStruct_020933ec obj;
    int field;

    func_02034270(&obj, arg2, 0, 0);
    field = obj.unk_34;

    if (field == 0x13 || (func_020b6598() != 0 && field == 3)) {
        int r = func_02094cf8(0x56, arg1, arg2, arg3, arg4, (void *) data_020e29dc);
        func_0203423c(&obj);
        return r;
    } else {
        func_0203423c(&obj);
        return 3;
    }
}
