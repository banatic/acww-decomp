/* func_02094ef4 @ 0x02094ef4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090db0(void *);

extern unsigned char data_021d5658[];

void func_02094ef4(void *arg0)
{
    unsigned int *puVar1;
    unsigned int *puVar2;
    unsigned int val;
    unsigned int val2;
    unsigned int val3;
    unsigned int *puVar6;

    puVar6 = (unsigned int *) data_021d5658;
    val = *puVar6;
    puVar1 = *(unsigned int **) ((int) arg0 + 0x18);
    val2 = *(unsigned int *) (*puVar1 + 4);
    *(unsigned int *) ((int) arg0 + 0x20) = val + val2;
    val = *(puVar6 + 1);
    puVar1 = *(unsigned int **) ((int) arg0 + 0x18);
    val2 = *(unsigned int *) (*puVar1 + 8);
    *(unsigned int *) ((int) arg0 + 0x24) = val + val2;
    val = *(puVar6 + 2);
    puVar1 = *(unsigned int **) ((int) arg0 + 0x18);
    val2 = *(unsigned int *) (*puVar1 + 0xc);
    *(unsigned int *) ((int) arg0 + 0x28) = val + val2;
    func_02090db0(arg0);
    return;
}
