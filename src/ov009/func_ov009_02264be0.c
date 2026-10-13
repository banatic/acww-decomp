/* func_ov009_02264be0 @ 0x02264be0, 0x30 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_022203dc(void *s, int index);
extern void func_02064328(void *a, void *b, int c, int d);

typedef struct {
    char pad_00[0x138];
    int unk_138;
} UnkStruct_02264be0;

typedef char GlobalType;
extern GlobalType data_ov009_02265b74;
extern GlobalType data_ov009_02265ad4;

char *func_ov009_02264be0(UnkStruct_02264be0 *s)
{
    int val;
    volatile int unused;
    val = s->unk_138;
    unused = func_ov003_022203dc(s, 0x138);
    func_02064328(&data_ov009_02265b74, &data_ov009_02265ad4, val, val);
    return &data_ov009_02265b74;
}
