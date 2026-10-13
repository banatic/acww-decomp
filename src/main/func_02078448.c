/* func_02078448 @ 0x02078448, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02078448 {
    unsigned short pad_00;
    unsigned char unk_02;
};

extern unsigned int func_02077898(struct UnkStruct_02078448 *);

unsigned int func_02078448(unsigned int *a, unsigned short *b, struct UnkStruct_02078448 *c)
{
    unsigned int ret;

    *a = c->unk_02;
    ret = func_02077898(c);
    *b = (unsigned short) ret;
    return ret;
}
