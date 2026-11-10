#include <iostream>
#include <cassert>
#include <bitcoin/bitcoin.hpp>

bc::hash_digest create_merkle(bc::hash_list merkle)
{
    if (merkle.empty()) return bc::null_hash;
    if (merkle.size() == 1) return merkle[0];

    while (merkle.size() > 1)
    {
        if (merkle.size() % 2 != 0)
        {
            merkle.push_back(merkle.back());
        }
        assert(merkle.size() % 2 == 0);

        return merkle[0];
    }

    return merkle[0];
}