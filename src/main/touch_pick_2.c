/* touch_pick_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b735c @ 0x020b735c, 0x28 bytes, Thumb
 * func_020b7338 @ 0x020b7338, 0x24 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int id;
} UnkStruct_02236204;

extern unsigned char data_020e54a8;
extern UnkStruct_02236204 *func_ov003_02236204(int id);
extern int (*data_020e57ac[])(int);

int func_020b735c(int a)
{
    unsigned int flag;
    int result;

    if (data_020e54a8 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (flag > 0) {
        result = (int) func_ov003_02236204(a);
    } else {
        result = 0;
    }

    return result;
}

int func_020b7338(int idx, int arg)
{
    if (idx < 23) {
        return data_020e57ac[idx](arg);
    } else {
        return 0;
    }
}
