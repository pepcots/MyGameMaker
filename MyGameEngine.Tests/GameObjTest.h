#pragma once

#include "../MyGameEngine/Tree.hpp"

class GameObjTest : public Tree<GameObjTest> {
private:
	const int _id;
public:
	inline int id() const { return _id; }
	explicit GameObjTest(int id);
};