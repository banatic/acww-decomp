/* func_02007d00 @ 0x02007d00, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c76a8[];

void func_02007d00(unsigned int arg0, unsigned int arg1)
{
    unsigned int val;
    unsigned int *puVar2;
    unsigned int *puVar3;
    unsigned int *puVar4;
    unsigned int *puVar5;

    if (data_020c76a8[arg1] == 0) {
        return;
    }
    puVar2 = (unsigned int *) (arg0 + 0x98);
    *puVar2 = 0;
    puVar3 = (unsigned int *) (arg0 + 0xa8);
    val = *puVar3;
    puVar4 = (unsigned int *) (arg0 + 0xa4);
    *puVar4 = 0;
    puVar5 = (unsigned int *) (arg0 + 0xa8);
    *puVar5 = val;
    *(unsigned int *) (arg0 + 0xac) = 0;
    return;
}
