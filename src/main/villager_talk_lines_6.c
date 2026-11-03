/* villager_talk_lines_6: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201f578 @ 0x0201f578, 0x8 bytes, Thumb
 * func_0201f570 @ 0x0201f570, 0x8 bytes, Thumb
 * func_0201f550 @ 0x0201f550, 0x20 bytes, Thumb
 * func_0201f520 @ 0x0201f520, 0x30 bytes, Thumb
 */

extern void func_0202a5e8(void *, void *);
extern void func_02020360(void *);

void func_0201f578(void *argument0, void *argument1)
{
    func_0202a5e8((void *) argument0, (void *) argument1);
}

void func_0201f570(void *argument0)
{
    func_02020360((void *) argument0);
}

int func_0201f550(unsigned short *p)
{
    int ret;
    unsigned int value;
    ret = 0;
    value = *p;
    if (value >= 0x1542 && value <= 0x1546) {
        ret = 1;
    }
    return ret;
}

unsigned short func_0201f520(unsigned short *param0, int param1)
{
    unsigned short r4;
    unsigned short r3;
    unsigned short r2;
    unsigned short r0;

    r4 = 0;
    r3 = 0;
    r2 = *param0;
    r0 = 0x1542;
    if (r2 >= r0) {
        r0 = 0x1546;
        if (r2 <= r0) {
            r3 = 1;
        }
    }
    if (r3 != 0) {
        if (param1 == 0) {
            r4 = 1;
        }
    }
    return r4;
}
