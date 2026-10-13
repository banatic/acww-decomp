/* func_0209ad2c @ 0x0209ad2c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(const void *p);
extern void *func_0209b4d4(const void *p);
extern int func_0209bd44(void *p);
extern void *func_0209b4cc(const void *p, int data);
extern int memcmp(const void *a, const void *b, int n);

void *func_0209ad2c(char *base, char *key, int data)
{
    void *result;
    char *elem;
    void *tmp;
    int i;

    result = 0;
    if (func_02003704(key)) {
        for (i = 0; i < 2; i++) {
            elem = base + i * 0x30;
            tmp = func_0209b4d4(elem);
            if (!func_0209bd44(tmp)) {
                continue;
            }
            tmp = func_0209b4cc(elem, data);
            if (*(unsigned short *) tmp != *(unsigned short *) key) {
                continue;
            }
            if (memcmp((char *) tmp + 2, key + 2, 12) != 0) {
                continue;
            }
            if (*(unsigned char *) ((char *) tmp + 0xf) != *(unsigned char *) (key + 0xf)) {
                continue;
            }
            result = elem;
            break;
        }
    }
    return result;
}
