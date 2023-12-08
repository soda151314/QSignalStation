#ifndef SINGLETON_H
#define SINGLETON_H

#define SINGLETON_DEFINE(TypeName)              \
static TypeName* instance()					\
{												\
    static TypeName type_instance;				\
    return &type_instance;						\
}												\
                                                \
TypeName(const TypeName&) = delete;				\
TypeName& operator=(const TypeName&) = delete;



#define SINGLETON_OBJ       instance()
#define SINGLETON_VAR(var)  instance()->var

#endif
