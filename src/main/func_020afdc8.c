/* func_020afdc8 @ 0x020afdc8, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
} UnkStruct_020afdc8;
typedef struct {
    void *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_020afdc8_2;

extern volatile unsigned char data_020e54a8;
extern UnkStruct_020afdc8_2 *data_021c80bc;
extern int func_020b65c4(void);
extern UnkStruct_020afdc8 *func_02037e0c(void *obj, int x, int y, int k);
extern int func_0204bcdc(void);
extern int func_0204bc64(UnkStruct_020afdc8 *e);
extern void func_020afe94(int x, int y, int a, int b);

void func_020afdc8(UnkStruct_020afdc8 *self, int p1, int p2)
{
    void *obj;
    int y, x;
    UnkStruct_020afdc8 *e;
    int ok;
    int flag;
    unsigned int z = 0;

    flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag != 0) {
        return;
    }
    if (func_020b65c4() != p1) {
        return;
    }
    if (data_021c80bc == 0) {
        return;
    }
    if (data_021c80bc->unk_04 > z && data_021c80bc->unk_08 > z && data_021c80bc->unk_00 != 0) {
        obj = data_021c80bc->unk_00;
    } else {
        obj = 0;
    }
    if (obj == 0) {
        return;
    }
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            e = func_02037e0c(obj, x, y, 0);
            if (e == 0) {
                continue;
            }
            if (func_0204bcdc() != 0) {
                int a = func_0204bc64(e);
                ok = (a == func_0204bc64(self)) ? 1 : 0;
            } else {
                ok = (e->unk_00 == self->unk_00) ? 1 : 0;
            }
            if (ok == 0) {
                continue;
            }
            func_020afe94(x, y, p1, p2);
            return;
        }
    }
}
