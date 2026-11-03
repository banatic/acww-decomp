/* villager_town_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207bfa4 @ 0x0207bfa4, 0x38 bytes, Thumb
 * func_0207bf38 @ 0x0207bf38, 0x6c bytes, Thumb
 * func_0207bee0 @ 0x0207bee0, 0x58 bytes, Thumb
 * func_0207be8c @ 0x0207be8c, 0x54 bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0207be8c;

typedef struct {
    char data[0x7ec];
} UnkStruct_0207be8c_2;

extern int func_0207c048(char *, int);
extern int func_0207bfdc(char *);
extern void func_0207dc30(char *, int);
extern void *func_0208150c(void *p);
extern int func_02003704(void *p);
extern void func_0207d978(void *p, void *arg);
extern void func_0207d91c(void *p, void *arg);
extern int func_0207d788(void *p, void *a, void *b, void *arg);
extern unsigned int func_0207f1c8(void *p);
extern int func_0209b5e8(int);
extern void func_0209baf4(void *);
extern int func_0209b5ec(void *);
extern int func_0209c2c0(void *);
extern int func_0209c020(int a, int b);
extern void func_0207f414(char *p, int a, int b);
extern UnkStruct_0207be8c *data_020ccf94;
extern int func_02073dd4(UnkStruct_0207be8c *p, int field);
extern void func_0209e474(void *buffer);
extern int func_0207d840(UnkStruct_0207be8c_2 *p, void *buffer);

void func_0207bfa4(char *a, int b)
{
    int result;
    result = func_0207c048(a, b);
    if (result != 0) {
        result = func_0207bfdc(a);
        if (result != -1) {
            func_0207dc30(a + result * 0x7EC, b);
        }
    }
}

void func_0207bf38(char *base, void *arg)
{
    char *p;
    int i;

    p = base;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) != 0) {
            func_0207d978(p, arg);
            func_0207d91c(p, arg);
            if (func_0207d788(p, base + 0x4050, base + 0x4058, arg) != 0xc) {
                func_0209baf4((void *) func_0209b5e8((int) func_0207f1c8(p)));
            }
        }
        p += 0x7ec;
    }
}

void func_0207bee0(char *p)
{
    int i = 0;
    volatile int local = 0;

    do {
        if (func_02003704(func_0208150c((void *) p))) {
            int r6;
            int r7;
            int result;

            r6 = (func_0209b5ec((void *) (void *) func_0207f1c8((void *) p)));
            r7 = func_0209c2c0((void *) r6);
            result = func_0209c020(r6, local);
            if (result != 0xc) {
                func_0207f414(p, result, r7);
            }
        }
        p += 0x7ec;
        i++;
    } while (i < 8);
}

void func_0207be8c(UnkStruct_0207be8c_2 *ptr)
{
    int i;
    int buffer[3];

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    buffer[0] = 0;
    buffer[1] = 0;
    func_0209e474(buffer);

    for (i = 0; i < 8; i++) {
        if (func_02003704((void *) (unsigned int) func_0208150c((void *) ptr))) {
            func_0207d840(ptr, buffer);
        }
        ptr++;
    }
}
