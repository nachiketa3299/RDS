#ifndef RDS_LIST_NODES_H
#define RDS_LIST_NODES_H

#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T>
struct snode_t
{
    snode_t* next;
    T val;
};

template <typename T>
struct dnode_t
{
    dnode_t* next;
    dnode_t* pref;
    T val;
};

RDS_END

#endif // RDS_LIST_NODES_H