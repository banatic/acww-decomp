/* func_0201ccc0 @ 0x0201ccc0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ccc0(void *arg0);

void func_0201ccc0(void *arg0)
{
    unsigned char *pbVar1;
    unsigned short *psVar2;

    pbVar1 = (unsigned char *) ((unsigned int) arg0 + 0x54);
    *pbVar1 = 5;
    psVar2 = (unsigned short *) ((unsigned int) arg0 + 0x56);
    *psVar2 = 0;
}
