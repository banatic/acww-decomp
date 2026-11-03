/* model_object_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020563c0 @ 0x020563c0, 0xc bytes, Thumb
 * func_020563b4 @ 0x020563b4, 0xc bytes, Thumb
 * func_0205639c @ 0x0205639c, 0x18 bytes, Thumb
 * func_02056390 @ 0x02056390, 0xc bytes, Thumb
 */

extern void func_020edb3c(void *p);
extern unsigned char data_020dd11c[];

void func_020563c0(unsigned int *out)
{
    *out = (unsigned int) ((unsigned char *) data_020dd11c);
}

void func_020563b4(unsigned int *out)
{
    *out = (unsigned int) ((unsigned int *) data_020dd11c);
}

void *func_0205639c(void *p)
{
    *(unsigned int *) p = (unsigned int) data_020dd11c;
    func_020edb3c(p);
    return p;
}

void func_02056390(void **ptr)
{
    *ptr = ((int *) data_020dd11c);
}
