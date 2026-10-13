/* func_02045d80 @ 0x02045d80, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

extern void func_02045cec(Pair *out, int arg);

void func_02045d80(Pair *src, int arg)
{
    Pair local;

    local.unk_00 = src->unk_00;
    local.unk_04 = src->unk_04;
    func_02045cec(&local, arg);
}
