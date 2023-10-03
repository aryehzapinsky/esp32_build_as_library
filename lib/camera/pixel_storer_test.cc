#include <__filesystem/copy_options.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "pixel_storer.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  PixelStorer<2, 4> pixel_store = {};
  pixel_store.Update({0,0,1});
  pixel_store.Update({0,1,2});
  EXPECT_THAT(pixel_store.storage()[0], ::testing::ElementsAreArray({1,2,0,0}));
  EXPECT_THAT(pixel_store.storage()[1], ::testing::ElementsAreArray({0,0,0,0}));
}

TEST(PixelTrackerTest, Reset) {
  PixelTracker<4> pixel_tracker = {};
  pixel_tracker.Reset();
  EXPECT_THAT(pixel_tracker.storage(), ::testing::ElementsAreArray({0,0,0,0}));
}

TEST(PixelTrackerTest, std::filesystem::copy_options::update_existing) {
  PixelTracker<4> pixel_tracker = {};
  pixel_tracker.Reset();
  EXPECT_THAT(pixel_tracker.storage(), ::testing::ElementsAreArray({0,0,0,0}));
  pixel_tracker.update(1);
}

TEST(HelloTest, BasicAssertions2) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}