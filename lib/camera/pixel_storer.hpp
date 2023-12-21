#ifndef LIB_CAMERA_PIXEL_STORER
#define LIB_CAMERA_PIXEL_STORER

#include <array>
#include <cstdint>
#include <cstddef>

struct Pixel{
  int row = 0;
  int column = 0;
  int value = 0;
};

template<std::size_t rows, std::size_t columns>
class PixelStorer {
 public:
  constexpr PixelStorer() {}
  explicit constexpr PixelStorer(const PixelStorer& storer) : storage_(storer.storage()) {}

  /** @brief Storage type for pixels, n rows of m columns of pixels. */
  using Storage = std::array<std::array<uint8_t, columns>, rows>;

  /** @brief Getter for access to stored pixels. */
  const Storage& storage() { return storage_; }

  // TODO: Add bounds checking.
  /** @brief Update the pixel specified at (row, column) with value. */
  void Update (Pixel pixel) { storage_[pixel.row][pixel.column] = pixel.value; }
 private:

  /**@brief Two dimensionsal array of pixels. */
  Storage storage_ = {};
};


template<std::size_t number_of_pixels>
class PixelTracker {
 public:
  /** @brief Storage type for pixels. */
  using Storage = std::array<uint8_t, number_of_pixels>;

  /** @brief Getter for access to stored pixels. */
  const Storage& storage() { return storage_; }

  /** @brief Reset the internal position counter of the array */
  void Reset() {
    storage_ = Storage();
    position_ = 0;
  }

  /** @brief Update the array at the current position and update the position. */
  void Update(uint8_t value) {
    storage_[position_++] = value;
  }
 private:

  /** @brief One dimensionsal array of pixels. */
  Storage storage_ = {};

  /** @brief Current position in storage.*/
  unsigned int position_ = 0;
};

#endif  // LIB_CAMERA_PIXEL_STORER
