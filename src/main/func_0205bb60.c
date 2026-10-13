/* func_0205bb60 @ 0x0205bb60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021ebcd4;
extern void *func_02060ee0(void *object, int index);
extern unsigned short *func_020611e8(void *pointer, int flag);

void func_0205bb60(unsigned short *out, int unused, int idx)
{
    unsigned short *value = func_020611e8(func_02060ee0(&data_021ebcd4, idx), 0);
    *out = *value;
}
