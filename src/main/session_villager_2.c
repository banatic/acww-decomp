/* session_villager_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02078448 @ 0x02078448, 0x16 bytes, Thumb
 * func_020783e0 @ 0x020783e0, 0x68 bytes, Thumb
 * func_020783a8 @ 0x020783a8, 0x38 bytes, Thumb
 * func_02078380 @ 0x02078380, 0x28 bytes, Thumb
 */

struct UnkStruct_02078448 {
    unsigned short pad_00;
    unsigned char unk_02;
};

extern unsigned int func_02077898(struct UnkStruct_02078448 *);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02078460(int *, void *, unsigned short *);
extern void func_02073820(void *);
extern void func_020737f0(void *, int *, int);
extern void func_02073770(void *, int, int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_020778b0(short *dest, unsigned short src);

unsigned int func_02078448(unsigned int *a, unsigned short *b, struct UnkStruct_02078448 *c)
{
    unsigned int ret;

    *a = c->unk_02;
    ret = func_02077898(c);
    *b = (unsigned short) ret;
    return ret;
}

void func_020783e0(void *a, unsigned short *b)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int flag = (*b >= 0x11a8) && (*b <= 0x12a7);
        if (flag) {
            int local;
            func_02078460(&local, a, b);
            {
                void *obj = data_020ccf94;
                func_02073820(obj);
                func_020737f0(obj, &local, 3);
                func_02073770(obj, 0x3a, 4);
            }
        }
    }
}

void func_020783a8(int param1, int param2)
{
    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) != 0) {
        param1 = func_0207f294(param1);
        if (func_0207cf74(param1) != 0) {
            func_020783e0((void *) param1, (unsigned short *) param2);
        }
    }
}

void func_02078380(short *dest, char value, unsigned short *src)
{
    int i;
    unsigned short *p = src;
    for (i = 0; i < 4; i++) {
        func_020778b0(&dest[i], *p);
        p++;
    }
    ((char *) dest)[8] = value;
}
