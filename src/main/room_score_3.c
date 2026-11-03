/* room_score_3: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205be44 @ 0x0205be44, 0x20 bytes, Thumb
 * func_0205be38 @ 0x0205be38, 0xc bytes, Thumb
 * func_0205be2c @ 0x0205be2c, 0xc bytes, Thumb
 * func_0205be20 @ 0x0205be20, 0xc bytes, Thumb
 * func_0205bdb0 @ 0x0205bdb0, 0x70 bytes, Thumb
 * func_0205bda0 @ 0x0205bda0, 0xe bytes, Thumb
 * func_0205bd90 @ 0x0205bd90, 0x10 bytes, Thumb
 * func_0205bd8c @ 0x0205bd8c, 0x2 bytes, Thumb
 * func_0205bd88 @ 0x0205bd88, 0x4 bytes, Thumb
 * func_0205bd84 @ 0x0205bd84, 0x4 bytes, Thumb
 * func_0205bd80 @ 0x0205bd80, 0x4 bytes, Thumb
 */

extern unsigned char data_021c95e4;
extern unsigned char data_021c95e8;
extern unsigned char data_021c95e0;
extern int func_0204df30(int);
extern void func_0205bbf4(void *, int);

unsigned char func_0205be38(void);
unsigned char func_0205be2c(void);
unsigned char func_0205be20(void);
int func_0205bd90(int arg);
void func_0205bd8c(void *object);
int func_0205bd88(unsigned char *p0);
int func_0205bd84(unsigned char *p0);
int func_0205bd80(unsigned char *p0);

int func_0205be44(void)
{
    return (int) func_0205be20() + ((int) func_0205be38() + (int) func_0205be2c());
}

unsigned char func_0205be38(void)
{
    return data_021c95e4;
}

unsigned char func_0205be2c(void)
{
    return data_021c95e8;
}

unsigned char func_0205be20(void)
{
    return data_021c95e0;
}

void func_0205bdb0(void)
{
    unsigned char buf[3];
    unsigned int i;

    data_021c95e0 = 0;
    data_021c95e8 = 0;
    data_021c95e4 = 0;

    for (i = 0; i < 5; i++) {
        int r;

        func_0205bd90((int) &buf);
        r = func_0204df30(i);
        if (r != 0) {
            func_0205bbf4(&buf, r);
            data_021c95e4 += func_0205bd88((unsigned char *) (&buf));
            data_021c95e8 += func_0205bd84((unsigned char *) (&buf));
            data_021c95e0 += func_0205bd80((unsigned char *) (&buf));
        }
        func_0205bd8c(&buf);
    }
}

void func_0205bda0(unsigned char *r0)
{
    unsigned char temp;

    r0[2] = 0;
    temp = r0[2];
    r0[1] = temp;
    temp = r0[1];
    r0[0] = temp;
}

int func_0205bd90(int arg)
{
    func_0205bda0((unsigned char *) arg);
    return arg;
}

void func_0205bd8c(void *object) {}

int func_0205bd88(unsigned char *p0)
{
    return p0[0];
}

int func_0205bd84(unsigned char *p0)
{
    return p0[1];
}

int func_0205bd80(unsigned char *p0)
{
    return p0[2];
}
