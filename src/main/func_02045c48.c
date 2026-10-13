/* func_02045c48 @ 0x02045c48, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02045cec(int *buffer, int flag);

int func_02045c48(void)
{
    int buffer[3];
    buffer[0] = 0xff;
    buffer[1] = 0xff;
    return func_02045cec(buffer, 0);
}
