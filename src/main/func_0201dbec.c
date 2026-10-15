/* func_0201dbec @ 0x0201dbec, 0x6c bytes, Thumb, module main
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

extern void func_0202da74(void *object, Pair value);

extern Pair data_020d91c8;
extern char data_021c22a4;
extern char data_021c22bc;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

void func_0201dbec(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x32, 0x32, (void *) &data_021c22a4);
    func_0201cf90(param, buf, 1, 0x33, 0x33, (void *) &data_021c22bc);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d91c8);
    func_02068388(param->unk_40, 1);
}
