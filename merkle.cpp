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

        bc::hash_list new_merkle;
        
        for (auto it = merkle.begin(); it != merkle.end(); it += 2)
        {
            bc::data_chunk data(bc::hash_size * 2);
            auto writer = bc::serializer<decltype(data.begin())>(data.begin());
            
            writer.write_hash(*it);
            writer.write_hash(*(it + 1));
            
            new_merkle.push_back(bc::bitcoin_hash(data));
        }

        merkle = new_merkle;
    }

    return merkle[0];
}

int main()
{
    bc::hash_list tx_hashes {{
        bc::hash_literal("8c14f0db3df150123e6f3dbbf30f8b955a8249b62ac1d1ff16284aefa3d06d87"),
        bc::hash_literal("fff2525b8931402dd09222c50775608575787bd2b87e56995a7bdd30f79702c4"),
        bc::hash_literal("6359f0868171b1d194cbeelaf2f16ea598ae8fad666d9b012c8ed2b79a236ec4"),
        bc::hash_literal("e9a66845e05d5abc0ad04ec80f774a7e585c6e8db975962d069a522137b80c1d")
    }};

    const bc::hash_digest merkle_root = create_merkle(tx_hashes);
    std::cout << "Merkle Root Hash: " << bc::encode_base16(merkle_root) << std::endl;
    
    return 0;
}