//Файл описания методов глобальной структуры map

#pragma once

struct _Map {
    void  (*destroy)(struct _Map* obj);
    int   (*insert)(struct _Map* obj, void* key, void* value);
    int   (*delete)(struct _Map* obj, void* key);
    int   (*change)(struct _Map* obj, void* key, void* newValue);
    void* (*get)(struct _Map* obj, void* key);
    int   (*compare_keys)(void* key1, void* key2);
    ///int   (*count_value)(struct _Map* obj, void* value); /// not need?
};
typedef struct _Map Map;

