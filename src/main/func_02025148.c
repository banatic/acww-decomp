/* func_02025148 @ 0x02025148, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    unsigned char b;
} Config;
typedef struct {
    int unk_00;
    int unk_04;
} Pair;
typedef struct {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x30];
    void *unk_100;
    char buf[30];
    unsigned char unk_122;
} UnkStruct_02025148;
typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02025148_2;
extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern Config data_020c8d08;
extern Config data_020c8d20;
extern Pair data_020d8f18;
void func_02025148(UnkStruct_02025148 *param0, UnkStruct_02025148_2 *param1)
{
    Config *config;
    int value;
    int result;
    config = &data_020c8d08;
    if (func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) param0)) == 1) {
        config = &data_020c8d20;
    }
    value = *((int *) (((char *) param0->unk_100) + 0x830));
    result = func_020036e8((unsigned char *) func_0208150c(value));
    func_0202da38(param0, param0->buf, (char *) (&param0->unk_122), 0x1e, result, config->a, (unsigned char) config->b, 0, 0);
    param1->ptr = param0->buf;
    param1->byte = param0->unk_122;
    param0->unk_C8 = data_020d8f18;
}
