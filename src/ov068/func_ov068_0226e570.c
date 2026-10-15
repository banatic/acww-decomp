/* func_ov068_0226e570 @ 0x0226e570, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_02098fd0(int, int);
extern int data_ov068_0227733c;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_ov068;

void func_ov068_0226e570(int arg0, UnkStruct_ov068 *arg1)
{
    int ret;
    ret = func_020984e8();
    if (ret != 0) {
        func_02098fd0(ret, 0x23);
    }
    arg1->unk_00 = data_ov068_0227733c;
    arg1->unk_04 = 0x22;
}
