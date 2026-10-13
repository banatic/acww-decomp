/* func_02041718 @ 0x02041718, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned char data_021c75b8;
extern int func_020b65c4(void);
extern int func_020a6c98(void);

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short unk_0C;
} UnkStruct_02041718;
extern UnkStruct_02041718 *data_021f42f4;

int func_02041718(void)
{
    int flag;

    flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag == 0) {
        return 0;
    }
    if (func_020b65c4() == 0x3f) {
        return 0;
    }
    if (func_020b65c4() == 0x2c) {
        return 0;
    }
    if (func_020b65c4() == 6) {
        return 0;
    }
    func_020b65c4();
    if (func_020a6c98() != 0) {
        return 0;
    }
    if (data_021f42f4 != 0) {
        if (data_021f42f4->unk_0C != 6) {
            return 0;
        }
    }
    return 1;
}
