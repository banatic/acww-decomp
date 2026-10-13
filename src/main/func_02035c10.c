/* func_02035c10 @ 0x02035c10, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c9f14[];

void func_02035c10(void *arg0, unsigned char arg1)
{
    unsigned char value;
    value = data_020c9f14[arg1];
    *(unsigned int *) ((char *) arg0 + 0xc) = value;
}
