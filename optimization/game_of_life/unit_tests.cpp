#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <iostream>
#include "game_of_life.hpp"
#include "utils.hpp"

const std::string biloaf_0{"......\n...#..\n..#.#.\n.#..#.\n..##..\n.#..#.\n.#.#..\n..#...\n......\n"};
const std::string biloaf_1{"......\n...#..\n..#.#.\n.#..#.\n.####.\n.#..#.\n.#.#..\n..#...\n......\n"};
const std::string biloaf_2{"........\n....#...\n...#.#..\n..#..##.\n.##..##.\n.##..#..\n..#.#...\n...#....\n........\n"};
const std::string biloaf_3{"........\n....#...\n...#.##.\n.###....\n...##...\n....###.\n.##.#...\n...#....\n........\n"};
const std::string biloaf_4{"........\n....##..\n...#.#..\n.....#..\n........\n..#.....\n..#.#...\n..##....\n........\n"};

const std::string block_0{"....\n.##.\n.##.\n....\n"};
const std::string blinker_0{".....\n.###.\n.....\n"};
const std::string glider_0{".....\n...#.\n.#.#.\n..##.\n.....\n"};
const std::string eater_1_0{"......\n.##...\n.#.#..\n...#..\n...##.\n......\n"};
const std::string herschel_0{".....\n.#...\n.###.\n.#.#.\n...#.\n.....\n"};

std::string state_after_x_iterations(const std::string &initial_state, const int iterations)
{
    std::vector<std::vector<bool>> state = decode_table(initial_state);
    for (int i = 0; i < iterations; i++)
        game_of_life_v1(state);
    return encode_table(state);
}

TEST(Decoding, DecodeBiloaf)
{
    std::string encoded_string{biloaf_0};
    std::vector<bool> l0 = {false, false, false, false, false, false};
    std::vector<bool> l1 = {false, false, false, true, false, false};
    std::vector<bool> l2 = {false, false, true, false, true, false};
    std::vector<bool> l3 = {false, true, false, false, true, false};
    std::vector<bool> l4 = {false, false, true, true, false, false};
    std::vector<bool> l5 = {false, true, false, false, true, false};
    std::vector<bool> l6 = {false, true, false, true, false, false};
    std::vector<bool> l7 = {false, false, true, false, false, false};
    std::vector<bool> l8 = {false, false, false, false, false, false};
    std::vector<std::vector<bool>> expected_state{l0, l1, l2, l3, l4, l5, l6, l7, l8};
    std::vector<std::vector<bool>> state = decode_table(encoded_string);

    for (size_t i = 0; i < expected_state.size(); i++)
        for (size_t j = 0; j < expected_state[0].size(); j++)
            EXPECT_EQ(state[i][j], expected_state[i][j]);
}

TEST(ENCODE, EncodeBiloaf)
{
    std::vector<bool> l0 = {false, false, false, false, false, false};
    std::vector<bool> l1 = {false, false, false, true, false, false};
    std::vector<bool> l2 = {false, false, true, false, true, false};
    std::vector<bool> l3 = {false, true, false, false, true, false};
    std::vector<bool> l4 = {false, false, true, true, false, false};
    std::vector<bool> l5 = {false, true, false, false, true, false};
    std::vector<bool> l6 = {false, true, false, true, false, false};
    std::vector<bool> l7 = {false, false, true, false, false, false};
    std::vector<bool> l8 = {false, false, false, false, false, false};
    std::vector<std::vector<bool>> state{l0, l1, l2, l3, l4, l5, l6, l7, l8};

    std::string expected_encoded_string{biloaf_0};
    EXPECT_STREQ(encode_table(state).c_str(), expected_encoded_string.c_str());
}

TEST(GAME_OF_LIFE, Variant1RunsSuccessfully)
{
    std::vector<std::vector<bool>> state = decode_table(biloaf_0);
    game_of_life_v1(state);
    EXPECT_EQ(encode_table(state), biloaf_1);
    game_of_life_v1(state);
    EXPECT_EQ(encode_table(state), biloaf_2);
    game_of_life_v1(state);
    EXPECT_EQ(encode_table(state), biloaf_3);
    game_of_life_v1(state);
    EXPECT_EQ(encode_table(state), biloaf_4);
}

TEST(GAME_OF_LIFE, Variant2RunsSuccessfully)
{
    std::vector<std::vector<bool>> biloaf = decode_table(biloaf_0);
    std::vector<std::vector<bool>> block = decode_table(block_0);
    std::vector<std::vector<bool>> blinker = decode_table(blinker_0);
    std::vector<std::vector<bool>> glider = decode_table(glider_0);
    std::vector<std::vector<bool>> eater_1 = decode_table(eater_1_0);
    std::vector<std::vector<bool>> herschel = decode_table(herschel_0);

    for (int i = 0; i < 4; i++)
    {
        game_of_life_v2(biloaf);
        game_of_life_v2(block);
        game_of_life_v2(blinker);
        game_of_life_v2(glider);
        game_of_life_v2(eater_1);
        game_of_life_v2(herschel);
    }

    EXPECT_STREQ(encode_table(biloaf).c_str(), biloaf_4.c_str());
    EXPECT_STREQ(encode_table(block).c_str(), state_after_x_iterations(block_0, 4).c_str());
    EXPECT_STREQ(encode_table(blinker).c_str(), state_after_x_iterations(blinker_0, 4).c_str());
    EXPECT_STREQ(encode_table(glider).c_str(), state_after_x_iterations(glider_0, 4).c_str());
    EXPECT_STREQ(encode_table(eater_1).c_str(), state_after_x_iterations(eater_1_0, 4).c_str());
    EXPECT_STREQ(encode_table(herschel).c_str(), state_after_x_iterations(herschel_0, 4).c_str());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}