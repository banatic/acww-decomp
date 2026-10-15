/* func_020a8248 @ 0x020a8248, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a82a8(unsigned char *);
extern int data_020d1d0c[];

int func_020a8248(unsigned char *argument0)
{
    return data_020d1d0c[func_020a82a8((unsigned char *) argument0)];
}
