/* func_020afd24 @ 0x020afd24, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02062f90(void *dst, unsigned int value);
extern void func_0203d7c4(unsigned int value, void *dst);
extern unsigned int func_020644cc(unsigned int value);
extern void func_02077f14(unsigned int ptr, void *data);
extern void func_02062f4c(void *dst);
extern unsigned char data_020e41c4[];

void func_020afd24(unsigned int param)
{
    unsigned char buffer[0x2c];
    func_02062f90(buffer, param);
    func_0203d7c4(3, buffer);
    func_02077f14(func_020644cc(2) + 4, data_020e41c4);
    func_02062f4c(buffer);
}
