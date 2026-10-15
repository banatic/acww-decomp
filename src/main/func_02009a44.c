/* func_02009a44 @ 0x02009a44, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Triple {
    unsigned int a, b, c;
};

extern unsigned int func_0200e92c(void *ptr);
extern void func_0200e90c(void *ptr, int a, int b, short c);
extern void func_02009a9c(void *ptr, struct Triple data, int arg);
extern int func_0200e894(void *ptr1, void *ptr2);
extern int func_0200e91c(void *ptr);

int func_02009a44(unsigned char *obj, unsigned int *data, int a3, int a4, short a5)
{
    char bufA[12];
    char bufB[20];

    if (*(unsigned int *) (obj + 0x7f0) == 0x6f) {
        return 0;
    }

    func_0200e92c(bufA);

    func_0200e90c(bufA, 0x6f, a4, a5);

    func_02009a9c(bufB, *(struct Triple *) data, a3);

    {
        int result = func_0200e894(obj, bufA);
        func_0200e91c(bufA);
        return result;
    }
}
