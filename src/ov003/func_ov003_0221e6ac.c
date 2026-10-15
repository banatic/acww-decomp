/* func_ov003_0221e6ac @ 0x0221e6ac, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221e6a0(void *argument0);
extern int func_020984e8(void);
extern int func_020989b4(int object);
extern unsigned char *func_02098090(int, unsigned int);
extern unsigned char func_02065ec0(unsigned char *entry);

int func_ov003_0221e6ac(void *obj)
{
    int something;
    int count;
    unsigned int i;
    unsigned char *entry;

    if (func_ov003_0221e6a0(obj) == 0) {
        goto fail;
    }

    something = func_020989b4(func_020984e8());
    if (something == 0) {
        goto fail;
    }

    count = 0;
    for (i = count; i < 10; i++) {
        if ((entry = func_02098090(something, i)) && func_02065ec0(entry)) {
            count++;
        }
    }

    return count;

fail:
    return 0;
}
