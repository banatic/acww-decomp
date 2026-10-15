/* func_0205d36c @ 0x0205d36c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c9d1c;
extern unsigned int data_021c9d00;
extern unsigned short data_021c9cfc;
extern char data_021c9d04;

extern void *func_0205d5a8(void *addr, unsigned char b);
extern int func_0203cfb0(void *x, void *y);
extern void func_020051b0(void *);
extern void __register_global_object(void *, void *, void *);
extern void func_0205d58c(void *addr, unsigned char b, unsigned short *out);

void func_0205d36c(unsigned char *p, void *param1)
{
    unsigned char b = *p;

    if (func_0203cfb0(func_0205d5a8(&data_021c9d1c, b), param1) != 0) {
        if ((data_021c9d00 & 1) == 0) {
            data_021c9cfc = 0xffff;
            __register_global_object((void *) (&data_021c9cfc), (((void *) func_020051b0)), (void *) (&data_021c9d04));
            data_021c9d00 |= 1;
        }
        func_0205d58c(&data_021c9d1c, b, &data_021c9cfc);
    }
}
