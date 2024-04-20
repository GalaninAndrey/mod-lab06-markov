// Copyright 2024 Galanin Andrey
#include <gtest/gtest.h>
#include <string>
#include "../include/textgen.h"

TEST(test1, PrefixInText) {
    GenerationText generator;
    generator.Learn("Hello world cheese", 2);
    std::map<prefix, std::vector<std::string> > statetab = generator.get();
    prefix prefix = { "Hello", "world" };
    EXPECT_EQ(prefix, statetab.begin()->first);
}

TEST(test2, PrefixSuffix) {
    GenerationText generator;
    generator.Learn("Hello world cheese", 2);
    generator.fprefix = {"Hello", "world"};
    EXPECT_EQ(generator.get().at(prefix)[0], "cheese");
}

TEST(test3, OnceSuffix) {
    GenerationText generator;
    generator.Learn("hello everybody but not why how hello hi beacuse", 1);
    std::string gen = generator.Create(150, 10);
    EXPECT_EQ(gen, "hello hi beacuse ");
}

TEST(test4, NotOnceSuffix) {
    GenerationText generator;
    generator.Learn("Hello everybody but not everybody hi how", 1);
    prefix prefix = {"everybody"};
    std::vector<std::string> suffix = { "but", "hi" };
    EXPECT_EQ(suffix, generator.get().at(prefix));
}

TEST(test5, CreateText) {
    GenerationText generator;
    std::map<prefix, std::vector<std::string> > string = {
        { { "why" }, { "everybody", "do" } },
        { { "what" }, { "everybody" } }
    };
    generator.set(string);
    std::string string = generator.Create(10, 1, 20);
    EXPECT_EQ("what everybody ", string);
}