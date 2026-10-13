/* func_020b8dc0 @ 0x020b8dc0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7c];
    int unk_7C;
} Owner;

typedef struct {
    int unk_00;
} Target;

extern Owner data_021f6ba0;
extern Target data_021f6b20;
extern void func_020b889c(Target *t);

void func_020b8dc0(void)
{
    data_021f6ba0.unk_7C = 0xa;
    func_020b889c(&data_021f6b20);
}
