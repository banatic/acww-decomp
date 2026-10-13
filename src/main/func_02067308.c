/* func_02067308 @ 0x02067308, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int strlen(void *ptr);
extern int strncmp(char *str, void *ptr, int offset);
extern char *data_020ccec4[];

char *func_02067308(void *unused, char *str)
{
    char **cur = data_020ccec4;
    char *elem;
    while ((elem = *cur) != 0) {
        int offset = strlen(elem);
        if (strncmp(str, elem, offset) == 0 && str[offset] == '_') {
            break;
        }
        cur++;
    }
    return elem;
}
