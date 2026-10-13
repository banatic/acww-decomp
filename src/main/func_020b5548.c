/* func_020b5548 @ 0x020b5548, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f4c7c;
extern unsigned char data_021f4c98;
extern unsigned char data_021f4c8c;
extern void func_020b55d0(void *);
extern void func_020b55b8(void *);
extern void __register_global_object(void *, void (*)(void *), void *);

void *func_020b5548(void)
{
    if ((data_021f4c7c & 1) == 0) {
        func_020b55d0(&data_021f4c98);
        __register_global_object(&data_021f4c98, func_020b55b8, &data_021f4c8c);
        data_021f4c7c |= 1;
    }
    return &data_021f4c98;
}
