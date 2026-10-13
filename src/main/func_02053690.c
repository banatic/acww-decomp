/* func_02053690 @ 0x02053690, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c8c48[];
extern void *func_0206e6e4(void *ptr);

typedef struct {
    unsigned char pad_00[0x1b];
    unsigned char unk_1B;
} UnkStruct_02053690;

extern UnkStruct_02053690 *func_0206e7bc(void *ptr, int value);

int func_02053690(int param)
{
    void *ptr;
    UnkStruct_02053690 *result;
    unsigned char val;

    if (param >= 0x6e9) {
        param = 0x6e8;
    }

    ptr = func_0206e6e4(data_021c8c48);
    result = func_0206e7bc(ptr, param);

    if (result != 0) {
        val = result->unk_1B;
    } else {
        val = 0;
    }

    return val << 12;
}
