/* func_0205f73c @ 0x0205f73c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0205f77c(void *arg0, unsigned char arg1);

extern unsigned char data_021cacd0[];

unsigned long func_0205f73c(unsigned char *arg0)
{
    unsigned char local_1;
    void *local_2;

    local_1 = *arg0;
    local_2 = (void *) data_021cacd0;
    return func_0205f77c(local_2, local_1);
}
