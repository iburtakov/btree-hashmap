//Файл описания методов глобальной структуры map

#pragma once

struct _Map
{
    void  (*destroy)(struct _Map* obj);
    struct _Map*   (*insert)(struct _Map* obj, void* key, void* value); ///!!! проблемы с возвращаемым типом
    int   (*delete)(struct _Map* obj, void* key);
    int   (*change)(struct _Map* obj, void* key, void* newValue);
    void* (*get)(struct _Map* obj, void* key);
    int   (*compare_keys)(void* key1, void* key2);
    int   (*count_value)(struct _Map* obj, void* value);
};
typedef struct _Map Map;

