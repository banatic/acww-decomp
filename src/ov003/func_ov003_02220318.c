/* func_ov003_02220318 @ 0x02220318, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220174(int);
extern int func_ov009_02262fd8(void *object);

int func_ov003_02220318(int a)
{
    int object;
    unsigned short x = (unsigned short) (a + 0x5001);
    if ((object = func_ov003_02220174(x)) != 0) {
        return func_ov009_02262fd8((void *) object);
    }
    return 0;
}
