/* func_0208cf28 @ 0x0208cf28, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *, const void *);
extern void func_0208a1ec(void *, int);
extern void *func_0208a144(void *);

typedef struct {
    unsigned char pad_00[0xC];
    unsigned char sub[0x14];
    int unk_20;
    unsigned char pad1[0xA9 - 0x20 - sizeof(int)];
    unsigned char unk_A9;
} UnkStruct_0208cf28;

typedef struct {
    int a;
    int b;
} TableEntry;

extern TableEntry data_020d5b3c[];

void func_0208cf28(UnkStruct_0208cf28 *param)
{
    int index;
    param->unk_20 = 3;
    if (param->unk_A9) {
        index = 0x2C;
    } else {
        index = 0x27;
    }
    func_0208a1f0(&param->sub, &data_020d5b3c[index]);
    func_0208a1ec(&param->sub, 1);
    func_0208a144(&param->sub);
}
