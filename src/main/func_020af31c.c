/* func_020af31c @ 0x020af31c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4a80[];
extern void func_020af880(void *object);
extern void func_020af038(void *object);
extern void func_02063ce0(void *object, unsigned char a, unsigned char b, unsigned char c);
extern void func_020aed60(void *object, unsigned int *counter);
extern void func_020aed38(void *object, int *counter);
extern void func_020aece8(void *object, unsigned int *counter);
extern void func_020aecb8(void *object, int *counter);
extern void func_020aec90(void *object, int *counter);
extern void func_020aec68(void *object, int *counter);
extern void func_020aec40(void *object, int *counter);
extern void func_020aebcc(void *object, int *counter);
extern void func_020aeb9c(void *object, int *counter);
extern void func_020aeb6c(void *object, int *counter);

void func_020af31c(void *object, unsigned char a, unsigned char b, unsigned char c)
{
    unsigned int counter;
    func_020af880(object);
    counter = 0;
    func_02063ce0(data_021f4a80, a, b, c);
    func_020aed60(object, &counter);
    func_020aed38(object, (int *) &counter);
    func_020aece8(object, &counter);
    func_020aecb8(object, (int *) &counter);
    func_020aec90(object, (int *) &counter);
    func_020aec68(object, (int *) &counter);
    func_020aec40(object, (int *) &counter);
    func_020aebcc(object, (int *) &counter);
    func_020aeb9c(object, (int *) &counter);
    func_020aeb6c(object, (int *) &counter);
    func_020af038(object);
}
