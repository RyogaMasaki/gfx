#include "utils.hpp"

namespace chrgfx
{
/**
 * Expands bits to fill out a full byte.
 */
u8 expand_bits(u8 data, u8 bitcount)
{
	// shamelessly stolen from MAME
	if(bitcount == 1) {
		return (data & 1) ? 0xff : 0x00;
	}
	if(bitcount == 2) {
		data &= 3;
		return (data << 6) | (data << 4) | (data << 2) | data;
	}
	if(bitcount == 3) {
		data &= 7;
		return (data << 5) | (data << 2) | (data >> 1);
	}
	if(bitcount == 4) {
		data &= 0xf;
		return (data << 4) | data;
	}
	if(bitcount == 5) {
		data &= 0x1f;
		return (data << 3) | (data >> 2);
	}
	if(bitcount == 6) {
		data &= 0x3f;
		return (data << 2) | (data >> 4);
	}
	if(bitcount == 7) {
		data &= 0x7f;
		return (data << 1) | (data >> 6);
	}
	return data;
}

/**
 * Returns a 32bit value with the specified number of bits set, starting from
 * the LSB
 * e.g. 5 bits = 0b00011111 = 0x0000001F
 */
u32 create_bitmask32(u8 bitcount)
{
	// max 32 bits
	if(bitcount > 31) {
		return 0xffffffff;
	}

	u32 bitmask{0};
	for(s16 mask_iter{0}; mask_iter < bitcount; ++mask_iter) {
		bitmask |= (bitmask << 1) | 1;
	}
	return bitmask;
}
/**
 * Returns a 16bit value with the specified number of bits set, starting from
 * the LSB
 * e.g. 5 bits = 0b00011111 = 0x001F
 */
u16 create_bitmask16(u8 bitcount)
{
	// max 16 bits
	if(bitcount > 15) {
		return 0xffff;
	}

	u16 bitmask{0};
	for(s16 mask_iter{0}; mask_iter < bitcount; ++mask_iter) {
		bitmask |= (bitmask << 1) | 1;
	}
	return bitmask;
}

/**
 * Returns an 8bit value with the specified number of bits set, starting from
 * the LSB
 * e.g. 5 bits = 0b00011111 = 0x1F
 */
u8 create_bitmask8(u8 bitcount)
{
	// max 8 bits
	if(bitcount > 7) {
		return 0xff;
	}

	u8 bitmask{0};
	for(s16 mask_iter{0}; mask_iter < bitcount; ++mask_iter) {
		bitmask |= (bitmask << 1) | 1;
	}
	return bitmask;
}

palette make_pal_random()
{
	palette outpal;
	outpal.reserve(256);

	for(size_t paliter = 0; paliter < 256;) {
		color temp_col{(png::byte)(rand() % 255), (png::byte)(rand() % 255),
									 (png::byte)(rand() % 255)};
		// todo: apparently png::color does not implement operator== so we'll need
		// to extend it someday...
		/*
		if(std::find(outpal.begin(), outpal.end(), temp_col) == outpal.end()) {
			outpal.push_back(temp_col);
			++paliter;
		}
		*/
		++paliter;
		outpal.push_back(temp_col);
	}

	return outpal;
}

/**
 * Determines the endianness of the local system
 */
bool is_system_bigendian()
{
	// shamelessly stolen from stack overflow
	// https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program/56191401#56191401
	const int value{0x01};
	const void *address = static_cast<const void *>(&value);
	const unsigned char *least_significant_address =
			static_cast<const unsigned char *>(address);
	return (*least_significant_address == 0x01) ? false : true;
}

const bool bigend_sys = is_system_bigendian();

} // namespace chrgfx