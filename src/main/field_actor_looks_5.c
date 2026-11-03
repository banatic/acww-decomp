/* field_actor_looks_5: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02011368 @ 0x02011368, 0x24 bytes, Thumb
 * func_02011340 @ 0x02011340, 0x28 bytes, Thumb
 * func_0201131c @ 0x0201131c, 0x24 bytes, Thumb
 * func_020112f8 @ 0x020112f8, 0x24 bytes, Thumb
 * func_020112e4 @ 0x020112e4, 0x12 bytes, Thumb
 * func_020112d0 @ 0x020112d0, 0x12 bytes, Thumb
 * func_020112bc @ 0x020112bc, 0x12 bytes, Thumb
 */

extern int func_02096284(int x);
extern int func_0209847c(void *);
extern int func_02099870(int);
extern int func_020950c0(signed char *);
extern unsigned short *func_02099710(int value);
extern int func_020996f8(int);
extern unsigned int func_02099824(const unsigned char *);
extern unsigned int func_020997f8(void *);
extern unsigned int func_020997d0(void *);

int func_02011368(void *arg)
{
    int res = func_02096284(*(unsigned int *) ((char *) arg + 0x800));
    if (res < 7) {
        return func_0209847c((void *) res);
    }
    return 0;
}

int func_02011340(void *argument0)
{
    int r1;
    int r0;

    r0 = func_02011368((void *) argument0);
    r1 = 0;
    if (r0 != 0) {
        r0 = func_020950c0((signed char *) func_02099870(r0));
        if (r0 != 0) {
            r1 = 1;
        } else {
            r1 = 0;
        }
    }
    return r1;
}

void func_0201131c(unsigned short *dest, int arg2)
{
    int tmp;
    tmp = func_02011368((void *) arg2);
    *dest = 0xfff1;
    if (tmp != 0) {
        *dest = *func_02099710(tmp);
    }
}

void func_020112f8(int param1, int param2)
{
    int result;
    int temp;

    result = func_02011368((void *) param2);
    *(unsigned short *) param1 = 0xfff1;
    if (result != 0) {
        temp = func_020996f8(result);
        *(unsigned short *) param1 = *(unsigned short *) temp;
    }
}

unsigned int func_020112e4(void *argument0)
{
    return func_02099824((const unsigned char *) func_02011368((void *) argument0));
}

unsigned int func_020112d0(void *argument0)
{
    return func_020997f8((void *) func_02011368((void *) argument0));
}

unsigned int func_020112bc(void *argument0)
{
    return func_020997d0((void *) func_02011368((void *) argument0));
}
