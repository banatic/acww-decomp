/* func_0202acec @ 0x0202acec, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern void func_0201cfb4(void *a, void *b);
extern void func_0201cf90(void *a, void *b, int c, int d, int e, int f);
extern void func_0201cec8(void *a, void *b);
extern void func_0202da74(void *a, Pair b);
extern void func_02068388(int a, int b);
extern Pair data_020d9268;

extern unsigned char data_021c2734[];
extern unsigned char data_021c2764[];

void func_0202acec(void *param)
{
    char local[0x22];
    func_0201cfb4(param, local);
    func_0201cf90(param, local, 0, 0x4a, 0x4a, (unsigned int) data_021c2764);
    func_0201cf90(param, local, 1, 0x49, 0x49, (unsigned int) data_021c2734);
    local[0x20] = 2;
    local[0x21] = -1;
    func_0201cec8(param, local);
    func_0202da74(param, data_020d9268);
    func_02068388(*(int *) ((char *) param + 0x40), 1);
}
