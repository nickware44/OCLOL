/*		OCLOL.h									*/
/*		OpenCL Optimization Library Header		*/
/*		version 1.0								*/
/*		NickWare Group							*/

#pragma once
#include <CL/cl.hpp>

class OCLOL
{
private:
	int CU, MWGS, PWGSM, Cores, OLWGS;
	long OGWGS, TaskVolume;
public:
	OCLOL(cl::Device, cl::Kernel, const long, const int);
	void PerformOptimization();
	long GetGlobalWorkGroupSize();
	int GetLocalWorkGroupSize();
	~OCLOL();
};
