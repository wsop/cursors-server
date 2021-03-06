#include "LevelObject.hpp"
#include "Level.hpp"

LevelObject::LevelObject(std::uint16_t x, std::uint16_t y,
                         std::uint16_t w, std::uint16_t h, ObjectType type)
: lvl(nullptr), id(0), opened_counter(0), 
  x(x), y(y), w(w), h(h), type(type) { };

LevelObject::~LevelObject() {
	if (lvl) {
		lvl->RemoveObject(this);
	}
}

void LevelObject::set_lvl(Level * lvl) {
	this->lvl = lvl;
}

void LevelObject::remove() {
	if (opened_counter == 0 && lvl) {
		lvl->RemoveObject(this);
	}
	++opened_counter;
}

void LevelObject::insert() {
	if (opened_counter != 0 && --opened_counter == 0 && lvl) {
		lvl->AddObject(this);
	}
}

bool LevelObject::click() {
	return false;
}

bool LevelObject::hover(Cursor * const) {
	return false;
}

bool LevelObject::player_left(Cursor * const) {
	return false;
}

bool LevelObject::tick() {
	return false;
}

void LevelObject::reset() {
	return;
}

void LevelObject::serialize(std::uint8_t * arr) {
	*(std::uint32_t *)(arr)      = id;
	*(std::uint8_t  *)(arr + 4)  = (std::uint8_t)type;
	*(std::uint16_t *)(arr + 5)  = x;
	*(std::uint16_t *)(arr + 7)  = y;
	*(std::uint16_t *)(arr + 9)  = w;
	*(std::uint16_t *)(arr + 11) = h;
}

size_t LevelObject::netsize() { /* 13 */
	return sizeof(std::uint32_t) + sizeof(std::uint8_t) + sizeof(std::uint16_t) * 4;
}

