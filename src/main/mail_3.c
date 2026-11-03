/* mail_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02097e28 @ 0x02097e28, 0x10 bytes, Thumb
 * func_02097e18 @ 0x02097e18, 0x10 bytes, Thumb
 * func_02097e14 @ 0x02097e14, 0x2 bytes, Thumb
 * func_02097e08 @ 0x02097e08, 0xc bytes, Thumb
 * func_02097dd4 @ 0x02097dd4, 0x34 bytes, Thumb
 */

typedef struct MailRecord_02097e14 {
    unsigned char data[0x100];
} MailRecord_02097e14;

extern void func_02066694(void *param);
extern void func_02066688(int arg);
extern void func_02066650(void *);

void *func_02097e28(void *param)
{
    func_02066694(param);
    return param;
}

int func_02097e18(int arg)
{
    func_02066688(arg);
    return arg;
}

unsigned char *func_02097e14(MailRecord_02097e14 *p)
{
    return p->data;
}

int func_02097e08(int a)
{
    return a + 0x100;
}

void func_02097dd4(unsigned char *arg0)
{
    func_02066650(arg0);
    arg0[0x100] = 1;
    arg0[0x101] = 1;
    arg0[0x102] = 0;
    arg0[0x103] = 0;
}
