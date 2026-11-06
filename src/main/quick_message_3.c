/* quick_message_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02039404 @ 0x02039404, 0x40 bytes, Thumb
 * func_020393ec @ 0x020393ec, 0x18 bytes, Thumb
 */

extern int data_020ca144[];
extern int data_020ca134[];
extern void func_02039efc(unsigned char *p, int i, int a, int b);
extern void func_0203931c(void *);
extern unsigned char data_021c6738[];

void func_02039404(unsigned char *base)
{
    int i;

    (*(unsigned char **) data_021c6738) = base;
    for (i = 0; i < 4; i++) {
        func_02039efc(base + 4 + i * 0xB8, i, data_020ca144[i], data_020ca134[i]);
    }
}

void func_020393ec(unsigned int *ptr)
{

    func_0203931c(ptr);
    ptr = (unsigned int *) data_021c6738;
    *ptr = 0;
}
