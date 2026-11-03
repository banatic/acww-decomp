/* room_object_life_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211558 @ 0x02211558, 0x1c bytes, Thumb
 * func_ov004_0221152c @ 0x0221152c, 0x2c bytes, Thumb
 * func_ov004_02211518 @ 0x02211518, 0x14 bytes, Thumb
 */

extern void *func_ov004_02210fdc(char *argument0);
extern void *memset(void *, int, int);
extern int func_ov004_0223ce98(void **argument0, int argument1);
extern int func_ov004_0223cf10(void);
extern void func_ov004_0223ce8c(void **heap, void *block);

int func_ov004_0221152c(char *self);

void func_ov004_02211558(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c((char *) 0x844)))) {
        func_ov004_02210fdc((char *) conditionInput0);
    }
}

int func_ov004_0221152c(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_ov004_0223ce98((void **) (func_ov004_0223cf10()), (int) (self));
    if (v2 == 0x0) {
        return 0x0;
    }
    memset((void *) (v2), 0x0, (int) (self));
    return v2;
}

void func_ov004_02211518(void *block)
{
    func_ov004_0223ce8c((void **) func_ov004_0223cf10(), block);
}
