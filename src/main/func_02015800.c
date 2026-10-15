/* func_02015800 @ 0x02015800, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02015800(void *arg0, unsigned short arg1, unsigned char arg2, unsigned char arg3)
{
    unsigned short *ptr1;
    int (**ptr2)(unsigned short *, int);
    unsigned char *ptr3;
    unsigned char *ptr4;
    unsigned short *ptr5;
    unsigned char *ptr6;

    ptr1 = (unsigned short *) ((char *) arg0 + 0x7c);
    *ptr1 = arg1;
    ptr2 = (int (**)(unsigned short *, int))((char *) arg0 + 0x78);
    *ptr2 = 0;
    ptr3 = (unsigned char *) ((char *) arg0 + 0x84);
    *ptr3 = arg2;
    ptr5 = (unsigned short *) ((char *) arg0 + 0x7e);
    *ptr5 = 0xfff1;
    ptr6 = (unsigned char *) ((char *) arg0 + 0x88);
    *ptr6 = arg3;
}
