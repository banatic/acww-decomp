/* func_020abd98 @ 0x020abd98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020abd98 {
    char pad_00[0xe4];
    unsigned char something;
    char pad_E5[0x141 - 0xe4 - 1];
    unsigned char flag;
};

extern int func_020aca54(unsigned char *ptr);

int func_020abd98(struct UnkStruct_020abd98 *p)
{
    if (p->flag != 0) {
        if (func_020aca54(&p->something) != 0) {
            return 1;
        }
    }
    return 0;
}
