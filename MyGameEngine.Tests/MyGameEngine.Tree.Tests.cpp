#include <CppUnitTest.h>
#include "GameObjTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyGameEngineTests
{
	TEST_CLASS(TreeTests)
	{
	public:
		TEST_METHOD(TreeAddsChildAndLinksParent)
		{
			GameObjTest root(1);
			auto& c11 = root.addChild(11);
			auto& c12 = root.addChild(12);
			auto& c111 = c11.addChild(111);
			auto& c112 = c11.addChild(112);
			Assert::IsTrue(root.children().begin()->children().begin()->id() == c111.id());
			Assert::IsTrue(c111.parent()->id()==c11.id());
			Assert::IsTrue(c11.parent()->id() == root.id());
		}
	};
}
