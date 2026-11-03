/* global_021dc5b0: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d084 @ 0x0209d084, 0x2 bytes, Thumb
 * func_0209d080 @ 0x0209d080, 0x2 bytes, Thumb
 * func_0209d074 @ 0x0209d074, 0xc bytes, Thumb
 * func_0209d068 @ 0x0209d068, 0xc bytes, Thumb
 */

extern unsigned char data_021dc5b0[];

void func_0209d084(void *self) {}

void func_0209d080(void *object) {}

void func_0209d074(unsigned char value)
{
    (*(unsigned char *) data_021dc5b0) = value;
}

unsigned char func_0209d068(void)
{
    return *((volatile unsigned char *) data_021dc5b0);
}
