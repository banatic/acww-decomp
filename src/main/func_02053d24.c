/* func_02053d24 @ 0x02053d24, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e4(void *addr);
extern void *func_0206e7bc(void *p, int value);

typedef struct {
    char pad_00[0x1e];
    unsigned char byte;
} UnkStruct_02053d24;

extern unsigned char data_021c8c48[];

int func_02053d24(int param)
{
    int value;
    void *tmp;
    UnkStruct_02053d24 *s;
    int result;

    value = param;
    if (value >= 0x6e9) {
        value = 0x6e8;
    }
    tmp = func_0206e6e4((void *) data_021c8c48);
    s = func_0206e7bc(tmp, value);
    if (s) {
        result = s->byte;
    } else {
        result = 0;
    }
    if (result == 0xff) {
        result = -1;
    }
    return result;
}
