/* func_0203ad88 @ 0x0203ad88, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc8];
    int unk_C8;
} Struct0203ad88;

extern Struct0203ad88 *data_021c67a4;
extern int func_0203c4e4(Struct0203ad88 *ptr);

int func_0203ad88(void)
{
    int ret;
    ret = func_0203c4e4(data_021c67a4);
    if (data_021c67a4->unk_C8 > ret) {
        return 0;
    } else {
        return 1;
    }
}
