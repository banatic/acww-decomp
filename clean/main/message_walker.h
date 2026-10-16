/* The walkers' base class (data_020e3e68; MessageWalker in message_cursor.h): its destructor
 * and its deleting destructor. */
#ifndef CLEAN_MAIN_MESSAGE_WALKER_H
#define CLEAN_MAIN_MESSAGE_WALKER_H

#include "message_cursor.h"

MessageWalker *MessageWalker_Destruct(MessageWalker *walker);
MessageWalker *MessageWalker_Delete(MessageWalker *walker);

#endif
