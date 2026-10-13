/* func_0202af6c @ 0x0202af6c, 0x70 bytes, Thumb, module main
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

extern Pair data_020d8f78;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

extern unsigned char data_021c271c[];
extern unsigned char data_021c277c[];

void func_0202af6c(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x4b, 0x4f, (void *) data_021c271c);
    func_0201cf90(param, buf, 1, 0x50, 0x54, (void *) data_021c277c);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d8f78);
    func_02068388(param->unk_40, 1);
}
