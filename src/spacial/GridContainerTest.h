/*
 * GridContainerTest.h
 *
 *  Created on: 22 Jun 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef GRIDCONTAINERTEST_H_
#define GRIDCONTAINERTEST_H_

namespace cryomesh {

namespace spacial {

class GridContainerTest {
public:
	GridContainerTest(){}
	virtual ~GridContainerTest(){}
	static void runSuite();
	static void testCreation();
	static void testGetSet();
};

}

}

#endif /* GRIDCONTAINERTEST_H_ */
