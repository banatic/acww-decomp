/* func_020b49d4 @ 0x020b49d4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f4dac;
extern void *func_020b4044(void *);
extern void func_020a8164(void *, int);
extern void func_020b43f4(void *);
extern void *func_020b4344(void *, void *);
extern void *func_020b402c(void *);

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[5];
    int int24;
    unsigned char unk_28;
    unsigned char pad_29[7];
} UnkStruct_020b49d4;

void *func_020b49d4(int a, unsigned char *b, int c)
{
    UnkStruct_020b49d4 local;
    void *result;
    func_020b4044(&local);
    func_020a8164(&local, c);
    local.unk_1E = *b;
    local.int24 = a;
    local.unk_28 = 1;
    func_020b43f4(&data_021f4dac);
    result = func_020b4344(&data_021f4dac, &local);
    func_020b402c(&local);
    return result;
}
