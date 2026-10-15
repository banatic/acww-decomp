/* func_02060448 @ 0x02060448, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0222a960(int, int);

typedef struct {
    unsigned char pad_00[0x2c];
    int unk_2C;
    unsigned char pad_30[0x0c];
    int unk_3C;
} UnkStruct_02060448;

void func_02060448(UnkStruct_02060448 *s)
{
    func_ov003_0222a960(s->unk_3C, 0);
    s->unk_2C = 0;
}
