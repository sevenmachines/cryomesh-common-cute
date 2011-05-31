/*
 * ActivityGridTest.h
 *
 *  Created on: 26 May 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef ACTIVITYGRIDTEST_H_
#define ACTIVITYGRIDTEST_H_

#include "ICuteSuite.h"

namespace cryomesh {

namespace spacial {

class ActivityGridTest {
public:
	ActivityGridTest(){}
	virtual ~ActivityGridTest(){}
	static  void runSuite();
	static void testCreation();
	static void testReScaling();
	static void testInterpolation();
	static  void testApplyGridActivityModifier();
	static  void testGetSetNearestGripPointActivity();
	static void testApplyPointActivity();
	static  void testApplyPointActivityToGrid();
	static  void testApplyPointActivityToGrid2();
	static  void testApplyPointActivityToGrid3();
	static  void testGetByActivity();
};

}

}

#endif /* ACTIVITYGRIDTEST_H_ */
