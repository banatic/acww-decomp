/* func_0203ed68 @ 0x0203ed68, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ed68(void *arg0, unsigned short arg1);

void func_0203ed68(void *arg0, unsigned short arg1)
{
    unsigned short *puVar1;
    unsigned short val;

    puVar1 = (unsigned short *) ((char *) arg0 + 0xe8);
    val = *puVar1;
    val = val | arg1;
    *(unsigned short *) ((char *) arg0 + 0xe8) = val;
}
