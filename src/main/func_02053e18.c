/* func_02053e18 @ 0x02053e18, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8c48;
typedef struct {
    char pad_00[0x16];
    unsigned short unk_16;
} UnkStruct_02053e18;
extern void *func_0206e6e4(void *a);
extern UnkStruct_02053e18 *func_0206e7bc(void *a, int b);

unsigned short func_02053e18(int param)
{
    int clamped;
    void *p;
    UnkStruct_02053e18 *s;
    clamped = param;
    if (clamped >= 0x6e9) {
        clamped = 0x6e8;
    }
    p = func_0206e6e4(&data_021c8c48);
    s = func_0206e7bc(p, clamped);
    if (s) {
        return s->unk_16;
    }
    return 0;
}
