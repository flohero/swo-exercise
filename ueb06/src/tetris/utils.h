//
// Created by florian on 01.12.20.
//

#ifndef SWO3_UTILS_H
#define SWO3_UTILS_H

extern void memory_error(bool condition, const char *func, int line);

#define out_of_memory(pointer) memory_error((pointer) == NULL, __func__, __LINE__)

#endif //SWO3_UTILS_H
