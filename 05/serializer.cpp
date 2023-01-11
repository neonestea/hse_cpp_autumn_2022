#include <iostream>
#include "serializer.hpp"
#include "deserializer.hpp"

struct DataIBI
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct DataBBI
{
    bool a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

/*int main()
{
    DataIBI x { 1, true, 2 };
    DataIBI y { 0, false, 0 };
    DataBBI z { true, false, 3 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    //assert(err == Error::NoError);

    //assert(x.a == y.a);
    //assert(x.b == y.b);
    //assert(x.c == y.c);

    return 0;
}*/
