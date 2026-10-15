/* func_0209dc48 @ 0x0209dc48, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209dc74(unsigned char *);

int func_0209dc48(unsigned char *arg0)
{
    unsigned char local_4[4];
    unsigned char *local_0;

    local_0 = local_4;
    local_4[0] = 1;
    local_4[1] = 1;
    local_4[2] = 0;
    local_4[3] = 0;
    local_4[2] = arg0[5];
    local_4[1] = arg0[4];
    local_4[0] = arg0[3];
    return func_0209dc74(local_4);
}
