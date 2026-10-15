/* func_020a8260 @ 0x020a8260, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a82a8(unsigned char *);
extern void *data_020d1ca8[];

void *func_020a8260(unsigned char *argument0)
{
    return data_020d1ca8[func_020a82a8((unsigned char *) argument0)];
}
