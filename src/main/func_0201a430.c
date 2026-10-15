/* func_0201a430 @ 0x0201a430, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206463c(void *object);
extern void *func_02082d90(void *p);
extern void *func_02082e78(void *p);
extern void *func_02082e04(void *p);
extern void *func_02056928(void *p);

void *func_0201a430(void *ptr)
{
    unsigned char *base = (unsigned char *) ptr;

    func_0206463c(ptr);
    func_02082d90(base + 4);
    func_02082e78(base + 0xc);
    func_02082e04(base + 0x14);
    func_02056928(base + 0x1c);
    func_02056928(base + 0x48);

    base[0x84] = 0;

    *(unsigned int *) (base + 0x74) = 0x16f;
    *(unsigned int *) (base + 0x78) = 0x16f;
    *(unsigned int *) (base + 0x7c) = 0x16f;
    *(unsigned int *) (base + 0x80) = 2;

    return ptr;
}
