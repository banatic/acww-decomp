/* func_ov102_0229c2c0 @ 0x0229c2c0, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229c318(void);

typedef struct {
    unsigned char pad_00[0x25aa];
    unsigned char data;
} UnkStruct_0229c2c0;

typedef struct {
    unsigned short pad_00;
    unsigned short flags;
} GlobalFlags;

extern GlobalFlags data_021fbe40;

int func_ov102_0229c2c0(UnkStruct_0229c2c0 *p)
{
    int flag;
    unsigned short fl;

    flag = 0;
    fl = data_021fbe40.flags;

    if (fl & 0x200) {
        flag = -1;
    } else if (fl & 0x100) {
        flag = 1;
    }

    if (flag != 0) {
        flag = flag + p->data;

        if (flag < 0) {
            flag = 5;
        } else if (flag >= 6) {
            flag = 0;
        }

        p->data = (unsigned char) flag;
        func_ov102_0229c318();
    }

    return 0;
}
