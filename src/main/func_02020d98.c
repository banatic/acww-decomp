/* func_02020d98 @ 0x02020d98, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} PairStruct;

typedef struct {
    char buffer[32];
    volatile unsigned char pair[2];
} FrameLocals;

extern void func_0201cf90(void *, void *, int, int, int, int);
extern void func_0201cec8(void *, void *);
extern void func_0202da74(void *, PairStruct);
extern void func_02068388(int, int);
extern const PairStruct data_020d9280;

extern unsigned char data_021c21cc[];
extern unsigned char data_021c21e4[];

void func_02020d98(void *param)
{
    FrameLocals locals;

    func_0201cf90(param, locals.buffer, 0, 0x37, 0x39, (unsigned int) data_021c21cc);
    func_0201cf90(param, locals.buffer, 1, 0x3a, 0x3c, (unsigned int) data_021c21e4);

    locals.pair[0] = 2;
    locals.pair[1] = locals.pair[0] - 1;

    func_0201cec8(param, locals.buffer);
    func_0202da74(param, data_020d9280);
    func_02068388(*(int *) ((char *) param + 0x40), 1);
}
