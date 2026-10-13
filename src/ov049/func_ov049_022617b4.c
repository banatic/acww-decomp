/* func_ov049_022617b4 @ 0x022617b4, 0x94 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int data_ov049_02263298;
extern int func_02073d90(void *);
extern short *func_0209d358(int, int);
extern void func_0206844c(int, char *, int);
extern int func_02082644(int);
extern void func_020160d8(void *, int);

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_022617b4;

void func_ov049_022617b4(UnkStruct_022617b4 *p, int type)
{
    void *obj;
    char buf[2];
    int res;

    obj = data_020ccf94;
    if (func_02073d90(obj) != 0 || ((short *) func_0209d358(0, 0x4a))[0] != 0) {
        if (type == 2) {
            buf[0] = 0x1c;
            func_0206844c(p->unk_40, &buf[0], data_ov049_02263298);
        } else if (type == 0) {
            buf[1] = 0x37;
            func_0206844c(p->unk_40, &buf[1], data_ov049_02263298);
        }
    }
    if (func_02073d90(obj) == 0 && ((short *) func_0209d358(0, 0x4a))[0] == 0) {
        res = func_02082644(5);
        if (res != 0) {
            func_020160d8(p, res);
        }
    }
}
