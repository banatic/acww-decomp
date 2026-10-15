/* func_020a8278 @ 0x020a8278, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a82a8(unsigned char *);
extern int data_020d1c44[];

int func_020a8278(unsigned char *argument0)
{
    return data_020d1c44[func_020a82a8((unsigned char *) argument0)];
}
