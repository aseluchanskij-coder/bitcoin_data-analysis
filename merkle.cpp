#include <iostream>
#include <bitcoin/bitcoin.hpp>

bc::hash_digest create_merkle(bc::hash_list merkle) //priima maisas, grazina sakni
{
    if (merkle.empty()) return bc::null_hash; //patikra kai ner transakciju
    if (merkle.size() == 1) return merkle[0]; //kai viena transakcija, tai ji is saves bus saknis

    return merkle[0];
}