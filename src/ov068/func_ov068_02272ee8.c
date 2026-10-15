/* func_ov068_02272ee8 @ 0x02272ee8, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02277750;
extern char data_ov068_02277814;
extern void *func_ov009_0226539c(void *);
extern void func_020edf54(void *);

typedef struct {
    unsigned int a;
    unsigned char pad_04[0xe8];
    unsigned int b;
} UnkStruct_02272ee8;

void *func_ov068_02272ee8(void *arg)
{
    UnkStruct_02272ee8 *obj = (UnkStruct_02272ee8 *) arg;
    obj->a = (unsigned int) &data_ov068_02277750;
    {
        char *q = (char *) obj;
        q += 0xec;
        *(unsigned int *) q = (unsigned int) &data_ov068_02277814;
    }
    func_ov009_0226539c(arg);
    func_020edf54(arg);
    return arg;
}
