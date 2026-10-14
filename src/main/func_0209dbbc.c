/* func_0209dbbc @ 0x0209dbbc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc744[];
extern unsigned char data_021dc754[];

unsigned int func_0209dbbc(void)
{
    unsigned int *base = (unsigned int *) data_021dc754;
    unsigned int *other = (unsigned int *) data_021dc744;
    return base[1] | ((other[2] << 8) | ((base[2] << 24) | (base[0] << 16)));
}
