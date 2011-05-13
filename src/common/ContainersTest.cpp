/**
 * ContainersTest.cpp
 *
 *  Created on: 31 Jan 2011
 *      Author: SevenMachines<SevenMachines@yahoo.co.uk>
 */

#include "ContainersTest.h"
#include "common/Containers.h"

namespace cryomesh {
namespace common {
void ContainersTest::runSuite() {
	cute::suite s;
	s.push_back(CUTE(ContainersTest::testAdd));
	s.push_back(CUTE(ContainersTest::testCompare));
	s.push_back(CUTE(ContainersTest::testDeleteByComparison));
	s.push_back(CUTE(ContainersTest::testFind));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "ContainersTest");
}
void ContainersTest::testCompare() {
	std::list<int> list1 = { 1, 2, 3 };
	std::list<int> list2 = { 1, 2, 3 };

	bool equality = (Containers::compare<std::list<int> >(list1, list2));
	ASSERT(equality);

}

void ContainersTest::testAdd() {
	std::list<int> list1 = { 1, 2, 3 };
	std::list<int> list2 = { 2, 3, 4 };

	std::list<int> list1copy = list1;
	std::list<int> list2copy = list2;

	std::list<int> list3 = Containers::add(list1, list2);
	std::list<int> list3expected = { 3, 5, 7 };

	//test equality
	{
		bool equality = (Containers::compare<std::list<int> >(list3expected, list3));
		ASSERT(equality);
	}
	//test equality
	{
		bool equality = (list1copy == list1);
		ASSERT(equality);
	}
	//test equality
	{
		bool equality = (list2copy == list2);
		ASSERT(equality);
	}

	// test merging in
	Containers::addMerge(list1, list2);

	//test equality
	{
		bool equality = (list3expected == list1);
		ASSERT(equality);
	}
	//test equality
	{
		bool equality = (list1copy == list1);
		ASSERT(!equality);
	}
	//test equality
	{
		bool equality = (list2copy == list2);
		ASSERT(equality);
	}
}

void ContainersTest::testDeleteByComparison() {
	std::multimap<int, int> tempmap;
	const int SIZE = 10;
	for (int i = 1; i < SIZE + 1; i++) {
		tempmap.insert(std::pair<int, int>(i, i));
	}

	ASSERT_EQUAL(SIZE, tempmap.size());

	//less than
	{
		Containers::deleteByComparison(4, tempmap, -1);
		ASSERT_EQUAL(SIZE-3, tempmap.size());
	}
	// > than
	{
		Containers::deleteByComparison(8, tempmap, 56);
		ASSERT_EQUAL(SIZE-5, tempmap.size());
	}
	//less than
	{
		Containers::deleteByComparison(5, tempmap, 0);
		ASSERT_EQUAL(SIZE-6, tempmap.size());
	}
}

void ContainersTest::testFind() {
	std::list < std::string > testlist( { "a", "b", "c" });

	// succeed
	{
		std::list<std::string>::const_iterator it_found = Containers::find<std::list<std::string>, std::string>(
				testlist, "a");
		ASSERT( it_found!= testlist.end());
	}

	// fail
	{
		std::list<std::string>::const_iterator it_found = Containers::find<std::list<std::string>, std::string>(
				testlist, "z");
		ASSERT( it_found == testlist.end());
	}
}
}//NAMESPACE
}//NAMESPACE
