/* func_020f9680 @ 0x020f9680, 0x30 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char unk_00;
    char sig[4];
    int unk_08;
    volatile int unk_0C;
    volatile int unk_10;
} UnkStruct_020f9680;

void func_020f9680(UnkStruct_020f9680 *s)
{
    s->sig[0] = -1;
    s->sig[1] = -1;
    s->sig[2] = -1;
    s->sig[3] = -1;
    s->unk_10 = 0;
    s->unk_0C = s->unk_10;
    s->unk_08 = s->unk_0C;
}
