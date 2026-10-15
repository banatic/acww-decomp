/* func_02045f08 @ 0x02045f08, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Pair;

extern int func_02045cec(Pair *out, int arg);
extern void func_02045eec(int);

void func_02045f08(Pair *src, int arg)
{
    Pair local;

    local.unk_00 = src->unk_00;
    local.unk_04 = src->unk_04;
    func_02045eec((int) func_02045cec(&local, arg));
}
