/* func_ov003_0221ffb0 @ 0x0221ffb0, 0x4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Server {
    unsigned char pad_00[0x20];
    struct Server *next;
} Server;

Server *func_ov003_0221ffb0(Server *server)
{
    return server->next;
}
