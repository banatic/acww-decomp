/* func_0200dc2c @ 0x0200dc2c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200dc48(void *param);
extern int func_02064594(int param);

int func_0200dc2c(void *param)
{
    int result;
    int offset;
    int value;

    result = func_0200dc48(param);
    offset = *(short *) ((char *) param + 0x8e);
    value = result - offset;
    value = (value << 16) >> 16;
    return func_02064594(value);
}
