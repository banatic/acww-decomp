/* func_020033c4 @ 0x020033c4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020033c4 {
    char pad_00[8];
    int unk_08;
};

extern char data_0213ff78;
extern struct UnkStruct_020033c4 *func_020ee7f0(void *a, void *b);

int func_020033c4(void *arg)
{
    struct UnkStruct_020033c4 *p;
    p = func_020ee7f0(&data_0213ff78, arg);
    if (p) {
        return p->unk_08;
    } else {
        return 0;
    }
}
