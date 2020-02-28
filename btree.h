#pragma once
#include "map.h"

//!
//! \param cmp (keys compare function)
//! \return binary tree container (type: struct _Map *)
Map * btree_create(int (*cmp)(void *, void *));

void TestAll();
void TestInsert();
void TestGet();
void TestDelete();
void TestChange();



