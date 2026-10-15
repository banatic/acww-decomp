/* func_ov126_0229fa38 @ 0x0229fa38, 0x48 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02070c08(void *buf);
extern int func_0206fc8c(void);
extern void func_02070934(void *buf, const char *data, int value);
extern int func_020707e8(void *buf, const char *ptr, unsigned char byte);
extern void func_0206fc4c(int value);
extern int **func_02070be8(void *buf);
extern const char data_ov126_022a2128[];

typedef struct {
    char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7[0x4248 - 0xa7];
    char unk_4248;
} UnkStruct_0229fa38;

void func_ov126_0229fa38(UnkStruct_0229fa38 *arg)
{
    char buf[0x70];
    int value;

    func_02070c08(buf);
    value = func_0206fc8c();
    func_02070934(buf, data_ov126_022a2128, value);
    if (func_020707e8(buf, &arg->unk_4248, arg->unk_A6) == 0) {
        func_0206fc4c(0);
    }
    func_02070be8(buf);
}
