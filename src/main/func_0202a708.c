/* func_0202a708 @ 0x0202a708, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201cfb4(void *param, void *buf);
extern void func_0201cf90(void *param, void *buf, int index, int a, int b, void *data);
extern void func_0201cec8(void *param, void *buf);
extern void func_02068388(int value, int flag);

typedef struct {
    int a;
    int b;
} Pair;

extern void func_0202da74(void *param, Pair p);

extern Pair data_020d93d8;
extern char data_021c280c;
extern char data_021c27f4;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

void func_0202a708(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x4a, 0x4a, (void *) &data_021c280c);
    func_0201cf90(param, buf, 1, 0x49, 0x49, (void *) &data_021c27f4);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d93d8);
    func_02068388(param->unk_40, 1);
}
