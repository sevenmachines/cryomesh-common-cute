/*
 * ActivityGridTest.cpp
 *
 *  Created on: 26 May 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "ActivityGridTest.h"

namespace cryomesh {

namespace spacial {

void ActivityGridTest::runSuite(){
	cute::suite s;
	s.push_back(CUTE( ActivityGridTest::testCreation));
	s.push_back(CUTE( ActivityGridTest::testReScaling));
	s.push_back(CUTE( ActivityGridTest::testInterpolation));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "ActivityGridTest");
}

void ActivityGridTest::testCreation(){
	ASSERTM("TODO", false);
}

void ActivityGridTest::testReScaling(){
	ASSERTM("TODO", false);
}

void ActivityGridTest::testInterpolation(){
	ASSERTM("TODO", false);
}

}//NAMESPACE

}//NAMESPACE
