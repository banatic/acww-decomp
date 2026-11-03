/* town_pelican_3: 7 functions, module ov075
 * mwccarm 1.2/base -O4,s
 * func_ov075_0227960c @ 0x0227960c, 0x118 bytes, Thumb
 * func_ov075_022795dc @ 0x022795dc, 0x30 bytes, Thumb
 * func_ov075_02279590 @ 0x02279590, 0x4c bytes, Thumb
 * func_ov075_02279584 @ 0x02279584, 0xc bytes, Thumb
 * func_ov075_02279558 @ 0x02279558, 0x2c bytes, Thumb
 * func_ov075_02279550 @ 0x02279550, 0x8 bytes, Thumb
 * func_ov075_02279548 @ 0x02279548, 0x8 bytes, Thumb
 */

extern void *func_020edf70(int size);
extern void *func_0203f130(void *arg0);
extern void *func_0205467c(void *p);
extern void func_0201b394(void *p);
extern void *func_0201a430(void *p);
extern int func_020169a8(void *p);
extern int func_0201b324(void *p);
extern void func_0201af14(void *p);
extern void func_0201b370(void *p);
extern void func_0201adec(void *p);
extern void *func_0201a7ec(void *p);
extern void func_0201a794(void *p);
extern void *func_02032c64(void *p);
extern void *func_02089c88(void *p);
extern void *func_020f55cc(void *p);
extern void func_02013c2c(void *p);
extern void *func_02019eb0(void *p);
extern void func_0201489c(void *p);
extern void *func_02082f60(void *p);
extern void *func_ov075_02278bb8(void *p);
extern int data_020d8c64;
extern int data_020da088;
extern int data_ov075_022799fc;
extern int func_0202edc8(void *object);
extern void func_0201c280(void *object, int value);
extern void func_ov075_02278b64(void *object, int value);
extern int func_0202ec58(void *arg0);
extern int func_0208602c(void);
extern int func_020860c0(int);
extern int func_02087e38(void *);
extern void func_ov075_022794b8(int, int);
extern int data_020c8120;
extern int func_0202ec14(void *parameter0);
extern int func_02041620(void);
extern void func_02087e64(int);
extern int data_ov075_02279948;
extern int data_ov075_02279900;

void *func_ov075_0227960c(void)
{
    void *ptr;

    ptr = func_020edf70(0x71c);
    if (ptr != 0) {
        func_0203f130((void *) ptr);
        *(void **) ptr = &data_020d8c64;
        *(unsigned short *) ((char *) ptr + 0xea) = 0xfff1;
        func_0205467c((char *) ptr + 0xec);

        func_0201b394((char *) ptr + 0x2a0);
        func_0201a430((char *) ptr + 0x2ac);
        func_020169a8((char *) ptr + 0x334);
        func_0201b324((char *) ptr + 0x350);
        func_0201af14((char *) ptr + 0x3a8);
        func_0201b370((char *) ptr + 0x3aa);
        func_0201adec((char *) ptr + 0x3b0);
        func_0201a7ec((char *) ptr + 0x418);
        func_0201a794((char *) ptr + 0x420);
        func_02032c64((char *) ptr + 0x49c);
        func_02089c88((char *) ptr + 0x4cc);
        func_020f55cc((char *) ptr + 0x514);
        func_02013c2c((char *) ptr + 0x558);
        func_02019eb0((char *) ptr + 0x564);
        func_0201489c((char *) ptr + 0x618);

        *(void **) ptr = &data_020da088;
        func_02082f60((char *) ptr + 0x640);
        *(void **) ptr = &data_ov075_022799fc;
        func_ov075_02278bb8((char *) ptr + 0x658);
    }

    return ptr;
}

int func_ov075_022795dc(void *this)
{
    if (!func_0202edc8(this)) {
        return 0;
    }
    func_0201c280(this, (int) ((char *) this + 0x658));
    func_ov075_02278b64(((char *) this + 0x658), (int) this);
    return 1;
}

int func_ov075_02279590(int param)
{
    int r4 = param;
    if (func_0202ec58((void *) param) == 0) {
        return 0;
    }
    if (func_02087e38((void *) func_020860c0((int) func_0208602c())) != 0) {
        func_ov075_022794b8(r4, 0);
    } else {
        func_ov075_022794b8(r4, 4);
    }
    *(int *) ((char *) r4 + 0x4e8) |= 2;
    return 1;
}

int func_ov075_02279584(void)
{
    return data_020c8120;
}

int func_ov075_02279558(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    } else {
        if (func_02041620() == 0) {
            func_02087e64((int) func_020860c0((int) func_0208602c()));
        }
        return 1;
    }
}

int func_ov075_02279550(void)
{
    return (int) &data_ov075_02279948;
}

int func_ov075_02279548(void)
{
    return (int) &data_ov075_02279900;
}
