/* object_actors_2: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022203ac @ 0x022203ac, 0xc bytes, Thumb
 * func_ov003_022203a0 @ 0x022203a0, 0xc bytes, Thumb
 * func_ov003_02220384 @ 0x02220384, 0x1a bytes, Thumb
 * func_ov003_02220368 @ 0x02220368, 0x1a bytes, Thumb
 * func_ov003_02220340 @ 0x02220340, 0x28 bytes, Thumb
 * func_ov003_02220318 @ 0x02220318, 0x28 bytes, Thumb
 */

extern unsigned char data_ov003_0223ce50;
extern int func_ov003_02220294(int argument0);
extern int func_ov009_0226305c(void *object);
extern int func_ov009_02262ff8(void *object);
extern int func_ov003_02220174(unsigned short val);
extern int func_ov009_0226303c(void *obj);
extern int func_ov009_02262fd8(void *object);

unsigned char func_ov003_022203ac(void)
{
    return data_ov003_0223ce50;
}

void func_ov003_022203a0(unsigned char r0)
{
    data_ov003_0223ce50 = r0;
}

int func_ov003_02220384(int argument0)
{
    int object = func_ov003_02220294(argument0);
    if (object) {
        return func_ov009_0226305c((void *) object);
    } else {
        return 0;
    }
}

int func_ov003_02220368(int argument0)
{
    int object = func_ov003_02220294(argument0);
    return object ? func_ov009_02262ff8((void *) object) : 0;
}

int func_ov003_02220340(int arg)
{
    int obj = func_ov003_02220174((unsigned short) (arg + 0x5001));
    if (obj != 0) {
        return func_ov009_0226303c((void *) obj);
    } else {
        return 0;
    }
}

int func_ov003_02220318(int a)
{
    int object;
    unsigned short x = (unsigned short) (a + 0x5001);
    if ((object = func_ov003_02220174(x)) != 0) {
        return func_ov009_02262fd8((void *) object);
    }
    return 0;
}
