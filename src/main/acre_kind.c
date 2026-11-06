/* acre_kind: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037c48 @ 0x02037c48, 0x30 bytes, Thumb
 * func_02037c28 @ 0x02037c28, 0x20 bytes, Thumb
 * func_02037c0c @ 0x02037c0c, 0x1c bytes, Thumb
 * func_02037bec @ 0x02037bec, 0x20 bytes, Thumb
 * func_02037bd8 @ 0x02037bd8, 0x12 bytes, Thumb
 * func_02037bc4 @ 0x02037bc4, 0x14 bytes, Thumb
 * func_02037b14 @ 0x02037b14, 0xb0 bytes, Thumb
 */

extern int func_02064b2c(void *p1, int val, int count, void *p2);
extern unsigned int data_021fbe94; // at 0x021fbe94
extern unsigned int data_021c590c; // at 0x021c590c
extern unsigned char data_020da4b4[];
extern unsigned char data_021c5910[];
extern void func_020e9898(int arg);
extern int data_020ca008[];

int func_02037bc4(int index);

int func_02037c48(void)
{
    data_021c590c = func_02064b2c(data_020da4b4, data_021fbe94, 4, data_021c5910);
    return 1;
}

int func_02037c28(void)
{
    func_020e9898((*(int *) &data_021c590c));
    (*(int *) &data_021c590c) = 0;
    return 1;
}

unsigned char func_02037c0c(unsigned int index)
{
    if (index < (*(unsigned int *) data_021c5910)) {
        return (*(unsigned char **) &data_021c590c)[index];
    }
    return 0;
}

int func_02037bec(int value)
{
    register int *ptr = data_020ca008;
    unsigned int i;
    for (i = 0; i < 55; i++) {
        if (value == *ptr++) {
            return (int) i;
        }
    }
    return 54;
}

int func_02037bd8(unsigned int argument0)
{
    return func_02037bc4((int) func_02037c0c((unsigned int) argument0));
}

int func_02037bc4(int index)
{
    if (index < 0x37) {
        return data_020ca008[index];
    } else {
        return 0;
    }
}

unsigned int func_02037b14(int index)
{
    unsigned int value = (unsigned int) func_02037bc4(index);
    if (value & 0x7f000) {
        unsigned char count = 0;
        if (value & 0x1000) {
            count++;
        }
        if (value & 0x2000) {
            count++;
        }
        if (value & 0x4000) {
            count++;
        }
        if (value & 0x8000) {
            count++;
        }
        if (value & 0x10000) {
            count++;
        }
        if (value & 0x20000) {
            count++;
        }
        if (value & 0x40000) {
            count++;
        }
        return count;
    }
    return 0;
}
