/* func_0201fed0 @ 0x0201fed0, 0x6c bytes, Thumb, module main
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

extern Pair data_020d9390;
extern char data_021c234c;
extern char data_021c231c;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

void func_0201fed0(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x5a, 0x5a, (void *) &data_021c234c);
    func_0201cf90(param, buf, 1, 0x6f, 0x6f, (void *) &data_021c231c);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d9390);
    func_02068388(param->unk_40, 1);
}
